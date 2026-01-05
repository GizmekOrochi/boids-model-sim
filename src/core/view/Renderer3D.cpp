#include "../../include/view/Renderer3D.hpp"
#include <algorithm>
#include <array>
#include <cmath>

namespace bd {

static sf::Color shadeFromDepth(float z) {
    // z is camera-space forward distance
    float t = 1.0f - std::min(std::max((z - 50.f) / 600.f, 0.f), 1.f);
    // brighter when closer
    int v = (int)(60 + 195 * t);
    return sf::Color(v, v, v);
}

Vec3<float> Renderer3D::worldToCamera(const Vec3<float>& p) const {
    // Convert world point into camera space using inverse camera rotation and translation.
    // Axes: X right, Y up, Z forward.
    Vec3<float> rel = p - camera.position;

    // Inverse yaw around Y (turn left/right)
    float cy = std::cos(-camera.yaw);
    float sy = std::sin(-camera.yaw);
    float x1 =  cy * rel.x + sy * rel.z;
    float y1 =  rel.y;
    float z1 = -sy * rel.x + cy * rel.z;

    // Inverse pitch around X (look up/down)
    float cp = std::cos(-camera.pitch);
    float sp = std::sin(-camera.pitch);
    float x2 = x1;
    float y2 =  cp * y1 - sp * z1;
    float z2 =  sp * y1 + cp * z1;

    return {x2, y2, z2};
}

bool Renderer3D::projectToScreen(const Vec3<float>& camP, Vec2<float>& out, float& outZ) const {
    // camP.z is forward distance; must be > nearZ
    if (camP.z <= nearZ) return false;

    float cx = (float)width * 0.5f;
    float cy = (float)height * 0.5f;

    out.x = (camP.x * fovPixels / camP.z) + cx;
    out.y = (camP.y * fovPixels / camP.z) + cy;
    outZ = camP.z;
    return true;
}

void Renderer3D::drawPyramid(sf::RenderWindow& win) {
    // World-space pyramid: base square in XZ plane, Y up.
    // Size tuned to look nice.
    std::vector<Vec3<float>> V = {
        {-80.f, 0.f,  80.f}, // 0 base
        { 80.f, 0.f,  80.f}, // 1
        { 80.f, 0.f, -80.f}, // 2
        {-80.f, 0.f, -80.f}, // 3
        {  0.f, 140.f, 0.f}  // 4 apex
    };

    // Triangles (two for base + 4 sides)
    std::vector<Face> faces = {
        {0, 1, 2}, {0, 2, 3}, // base
        {0, 1, 4},
        {1, 2, 4},
        {2, 3, 4},
        {3, 0, 4},
    };

    // Project vertices to screen (store camera-space z for depth)
    std::vector<Vec2<float>> P(V.size());
    std::vector<float> Z(V.size(), 0.f);
    std::vector<bool> ok(V.size(), false);

    for (size_t i = 0; i < V.size(); ++i) {
        Vec3<float> camP = worldToCamera(V[i]);
        ok[i] = projectToScreen(camP, P[i], Z[i]);
    }

    // Painter sort faces by average depth (far -> near)
    std::vector<int> order(faces.size());
    for (size_t i = 0; i < faces.size(); ++i) order[i] = (int)i;

    std::sort(order.begin(), order.end(), [&](int ia, int ib) {
        const Face& A = faces[ia];
        const Face& B = faces[ib];
        float za = (Z[A.a] + Z[A.b] + Z[A.c]) / 3.f;
        float zb = (Z[B.a] + Z[B.b] + Z[B.c]) / 3.f;
        return za > zb; // draw far first
    });

    // Draw filled triangles
    for (int idx : order) {
        const Face& f = faces[idx];

        if (!(ok[f.a] && ok[f.b] && ok[f.c]))
            continue;

        sf::ConvexShape tri;
        tri.setPointCount(3);
        tri.setPoint(0, sf::Vector2f(P[f.a].x, P[f.a].y));
        tri.setPoint(1, sf::Vector2f(P[f.b].x, P[f.b].y));
        tri.setPoint(2, sf::Vector2f(P[f.c].x, P[f.c].y));

        float avgZ = (Z[f.a] + Z[f.b] + Z[f.c]) / 3.f;
        tri.setFillColor(shadeFromDepth(avgZ));
        tri.setOutlineThickness(1.f);
        tri.setOutlineColor(sf::Color(30, 200, 255, 120));
        win.draw(tri);
    }

    // Wireframe edges (nice for debugging)
    auto drawEdge = [&](int a, int b) {
        if (!(ok[a] && ok[b])) return;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(P[a].x, P[a].y), sf::Color(255,255,255,170)),
            sf::Vertex(sf::Vector2f(P[b].x, P[b].y), sf::Color(255,255,255,170)),
        };
        win.draw(line, 2, sf::Lines);
    };

    drawEdge(0,1); drawEdge(1,2); drawEdge(2,3); drawEdge(3,0);
    drawEdge(0,4); drawEdge(1,4); drawEdge(2,4); drawEdge(3,4);
}

} // namespace bd
