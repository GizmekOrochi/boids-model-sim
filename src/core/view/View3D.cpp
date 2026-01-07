#include "../../include/view/View3D.hpp"
#include <algorithm>
#include <cmath>


namespace bd {

View3D::View3D(int w, int h) : width(w), height(h) {}

Camera& View3D::getCamera() {
    return camera;
}

void View3D::setViewport(int w, int h) {
    width = w;
    height = h;
}

// Transforme un point du repere monde vers le repere caméra
Vec3<float> View3D::worldToCamera(const Vec3<float>& p) const {
    Vec3<float> rel = p - camera.getPosition();

    float yaw = camera.getYaw();
    float pitch = camera.getPitch();

    float cy = std::cos(-yaw);
    float sy = std::sin(-yaw);
    float x1 =  cy * rel.x + sy * rel.z;
    float y1 = rel.y;
    float z1 = -sy * rel.x + cy * rel.z;

    float cp = std::cos(-pitch);
    float sp = std::sin(-pitch);
    float x2 = x1;
    float y2 = cp * y1 - sp * z1;
    float z2 = sp * y1 + cp * z1;

    return {x2, y2, z2};
}

// Projette un point de l'espace caméra sur l'ecran
bool View3D::projectToScreen(const Vec3<float>& camP, Vec2<float>& out, float& outZ) const {
    if (camP.z <= nearZ)
        return false;

    float cx = width * 0.5f;
    float cy = height * 0.5f;

    out.x = (camP.x * fovPixels / camP.z) + cx;
    out.y = (camP.y * fovPixels / camP.z) + cy;
    outZ = camP.z;

    return true;
}

void View3D::drawLine3D(sf::RenderWindow& win, const Vec3<float>& a, const Vec3<float>& b,sf::Color color) {
    Vec2<float> pa, pb;
    float za, zb;

    Vec3<float> ca = worldToCamera(a);
    Vec3<float> cb = worldToCamera(b);

    if (!projectToScreen(ca, pa, za)) return;
    if (!projectToScreen(cb, pb, zb)) return;

    sf::Vertex line[] = {
        sf::Vertex({pa.x, pa.y}, color),
        sf::Vertex({pb.x, pb.y}, color)
    };

    win.draw(line, 2, sf::Lines);
}

void View3D::drawTriangle3D(sf::RenderWindow& win, const Vec3<float>& a, const Vec3<float>& b, const Vec3<float>& c, sf::Color color) {
    drawLine3D(win, a, b, color);
    drawLine3D(win, b, c, color);
    drawLine3D(win, c, a, color);
}

void View3D::drawWorldCage(sf::RenderWindow& win) {
    const float W = settings::worldWidth;
    const float H = settings::worldHeight;
    const float D = settings::worldDeepth;

    sf::Color edgeColor(200, 200, 200, 180);
    sf::Color gridColor(100, 100, 100, 120);

    // ---- corners ----
    Vec3<float> A{0, 0, 0};
    Vec3<float> B{W, 0, 0};
    Vec3<float> C{W, H, 0};
    Vec3<float> D0{0, H, 0};

    Vec3<float> E{0, 0, D};
    Vec3<float> F{W, 0, D};
    Vec3<float> G{W, H, D};
    Vec3<float> H0{0, H, D};

    drawLine3D(win, A, B, edgeColor);
    drawLine3D(win, B, C, edgeColor);
    drawLine3D(win, C, D0, edgeColor);
    drawLine3D(win, D0, A, edgeColor);

    drawLine3D(win, E, F, edgeColor);
    drawLine3D(win, F, G, edgeColor);
    drawLine3D(win, G, H0, edgeColor);
    drawLine3D(win, H0, E, edgeColor);

    drawLine3D(win, A, E, edgeColor);
    drawLine3D(win, B, F, edgeColor);
    drawLine3D(win, C, G, edgeColor);
    drawLine3D(win, D0, H0, edgeColor);

    constexpr int GRID = 10;

    for (int i = 1; i < GRID; ++i) {
        float x = W * i / GRID;
        float y = H * i / GRID;

        drawLine3D(win, {x, 0, 0}, {x, H, 0}, gridColor);
        drawLine3D(win, {0, y, 0}, {W, y, 0}, gridColor);

        drawLine3D(win, {x, 0, D}, {x, H, D}, gridColor);
        drawLine3D(win, {0, y, D}, {W, y, D}, gridColor);
    }

    for (int i = 1; i < GRID; ++i) {
        float x = W * i / GRID;
        float z = D * i / GRID;

        drawLine3D(win, {x, 0, 0}, {x, 0, D}, gridColor);
        drawLine3D(win, {0, 0, z}, {W, 0, z}, gridColor);

        drawLine3D(win, {x, H, 0}, {x, H, D}, gridColor);
        drawLine3D(win, {0, H, z}, {W, H, z}, gridColor);
    }

    for (int i = 1; i < GRID; ++i) {
        float y = H * i / GRID;
        float z = D * i / GRID;

        drawLine3D(win, {0, y, 0}, {0, y, D}, gridColor);
        drawLine3D(win, {0, 0, z}, {0, H, z}, gridColor);

        drawLine3D(win, {W, y, 0}, {W, y, D}, gridColor);
        drawLine3D(win, {W, 0, z}, {W, H, z}, gridColor);
    }
}



void View3D::drawBoid(sf::RenderWindow& win, const Vec3<float>& position,const Vec3<float>& direction, Species::BoidSpecies BoidSpecie) {
    const float length = 18.0f;
    const float width = 6.0f;
    const float height = 6.0f;

    Vec3<float> forward = direction.normalized();
    Vec3<float> worldUp = (std::abs(forward.y) > 0.99f) ? Vec3<float>{1.f, 0.f, 0.f} : Vec3<float>{0.f, 1.f, 0.f};
    Vec3<float> right = worldUp.cross(forward).normalized();
    Vec3<float> up = forward.cross(right);

    // Piramide description ( top vertical then base verticals )
    std::vector<Vec3<float>> local = {
        { 0.f, 0.f, length },
        {-width, -height, 0.f},
        { width, -height, 0.f},
        { width, height, 0.f},
        {-width, height, 0.f}
    };

    std::vector<Vec3<float>> world(local.size());
    for (size_t i = 0; i < local.size(); ++i) {
        world[i] = position + right * local[i].x + up * local[i].y + forward * local[i].z;
    }

    static constexpr Face faces[] = {
        {0,1,2},
        {0,2,3},
        {0,3,4},
        {0,4,1}
    };

    if(BoidSpecie == Species::BoidSpecies::CYAN) {
        for (const Face& f : faces) {
            drawTriangle3D(win, world[f.a], world[f.b], world[f.c], sf::Color::Cyan);
        }
    }
    else if(BoidSpecie == Species::BoidSpecies::GREEN) {
        for (const Face& f : faces) {
            drawTriangle3D(win, world[f.a], world[f.b], world[f.c], sf::Color::Green);
        }
    }
    else if(BoidSpecie == Species::BoidSpecies::YELLOW) {
        for (const Face& f : faces) {
            drawTriangle3D(win, world[f.a], world[f.b], world[f.c], sf::Color::Yellow);
        }
    }
    else if(BoidSpecie == Species::BoidSpecies::BLUE) {
        for (const Face& f : faces) {
            drawTriangle3D(win, world[f.a], world[f.b], world[f.c], sf::Color::Blue);
        }
    }
    else {
        for (const Face& f : faces) {
            drawTriangle3D(win, world[f.a], world[f.b], world[f.c], sf::Color::Red);
        }
    }
}


void View3D::drawObstacle(sf::RenderWindow& win, const Vec3<float>& position, int sizeX, int sizeY, int sizeZ) {
    const float width  = static_cast<float>(sizeX);
    const float height = static_cast<float>(sizeY);
    const float Depth  = static_cast<float>(sizeZ);

    // Cube description
    std::vector<Vec3<float>> local = {
        {-width/2, -height/2, -Depth/2},
        { width/2, -height/2, -Depth/2},
        { width/2, -height/2, Depth/2},
        {-width/2, -height/2, Depth/2},
        {-width/2, height/2, -Depth/2},
        { width/2, height/2, -Depth/2},
        { width/2, height/2, Depth/2},
        {-width/2, height/2, Depth/2},
    };

    std::vector<Vec3<float>> world(local.size());
        for (size_t i = 0; i < local.size(); ++i) {
            world[i] = position + local[i];
        }

    sf::Color color = sf::Color::White;

    // bottom face
    drawLine3D(win, world[0], world[1], color);
    drawLine3D(win, world[1], world[2], color);
    drawLine3D(win, world[2], world[3], color);
    drawLine3D(win, world[3], world[0], color);

    drawLine3D(win, world[4], world[5], color);
    drawLine3D(win, world[5], world[6], color);
    drawLine3D(win, world[6], world[7], color);
    drawLine3D(win, world[7], world[4], color);

    drawLine3D(win, world[0], world[4], color);
    drawLine3D(win, world[1], world[5], color);
    drawLine3D(win, world[2], world[6], color);
    drawLine3D(win, world[3], world[7], color);
}


} // namespace bd
