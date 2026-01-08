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
MathsVector<float, 3> View3D::worldToCamera(const MathsVector<float, 3>& position) const {
    MathsVector<float, 3> rel{position - camera.getPosition()};

    float yaw = camera.getYaw();
    float pitch = camera.getPitch();

    float cy{std::cos(-yaw)};
    float sy{std::sin(-yaw)};
    float x1 = cy * rel[0] + sy * rel[2];
    float y1 = rel[1];
    float z1 = -sy * rel[0] + cy * rel[2];

    float cp{std::cos(-pitch)};
    float sp{std::sin(-pitch)};
    float x2{x1};
    float y2{cp * y1 - sp * z1};
    float z2{sp * y1 + cp * z1};

    return MathsVector<float, 3>{{x2, y2, z2}};
}

// Projette un point de l'espace caméra sur l'ecran
bool View3D::projectToScreen(const MathsVector<float, 3>& camP, MathsVector<float, 2>& out, float& outZ) const {
    if (camP[2] <= nearZ)
        return false;

    float cx{width * 0.5f};
    float cy{height * 0.5f};

    out[0] = (camP[0] * fovPixels / camP[2]) + cx;
    out[1] = (camP[1] * fovPixels / camP[2]) + cy;
    outZ = camP[2];

    return true;
}

void View3D::drawLine3D(sf::RenderWindow& win, const MathsVector<float, 3>& a, const MathsVector<float, 3>& b,sf::Color color) {
    MathsVector<float, 2> pa, pb;
    float za, zb;

    MathsVector<float, 3> ca{worldToCamera(a)};
    MathsVector<float, 3> cb{worldToCamera(b)};

    if (!projectToScreen(ca, pa, za)) return;
    if (!projectToScreen(cb, pb, zb)) return;

    sf::Vertex line[]{
        sf::Vertex({pa[0], pa[1]}, color),
        sf::Vertex({pb[0], pb[1]}, color)
    };

    win.draw(line, 2, sf::Lines);
}

void View3D::drawTriangle3D(sf::RenderWindow& win, const MathsVector<float, 3>& a, const MathsVector<float, 3>& b, const MathsVector<float, 3>& c, sf::Color color) {
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
    MathsVector<float, 3> A{{0.0f, 0.0f, 0.0f}};
    MathsVector<float, 3> B{{W, 0.0f, 0.0f}};
    MathsVector<float, 3> C{{W, H, 0.0f}};
    MathsVector<float, 3> D0{{0.0f, H, 0.0f}};

    MathsVector<float, 3> E{{0.0f, 0.0f, D}};
    MathsVector<float, 3> F{{W, 0.0f, D}};
    MathsVector<float, 3> G{{W, H, D}};
    MathsVector<float, 3> H0{{0.0f, H, D}};

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

        drawLine3D(win, MathsVector<float, 3>{{x, 0.0f, 0.0f}}, MathsVector<float, 3>{{x, H, 0.0f}}, gridColor);
        drawLine3D(win, MathsVector<float, 3>{{0.0f, y, 0.0f}}, MathsVector<float, 3>{{W, y, 0.0f}}, gridColor);

        drawLine3D(win, MathsVector<float, 3>{{x, 0.0f, D}}, MathsVector<float, 3>{{x, H, D}}, gridColor);
        drawLine3D(win, MathsVector<float, 3>{{0.0f, y, D}}, MathsVector<float, 3>{{W, y, D}}, gridColor);
    }

    for (int i = 1; i < GRID; ++i) {
        float x = W * i / GRID;
        float z = D * i / GRID;

        drawLine3D(win, MathsVector<float, 3>{{x, 0.0f, 0.0f}}, MathsVector<float, 3>{{x, 0.0f, D}}, gridColor);
        drawLine3D(win, MathsVector<float, 3>{{0.0f, 0, z}}, MathsVector<float, 3>{{W, 0.0f, z}}, gridColor);

        drawLine3D(win, MathsVector<float, 3>{{x, H, 0.0f}}, MathsVector<float, 3>{{x, H, D}}, gridColor);
        drawLine3D(win, MathsVector<float, 3>{{0.0f, H, z}}, MathsVector<float, 3>{{W, H, z}}, gridColor);
    }

    for (int i = 1; i < GRID; ++i) {
        float y = H * i / GRID;
        float z = D * i / GRID;

        drawLine3D(win, MathsVector<float, 3>{{0.0f, y, 0.0f}}, MathsVector<float, 3>{{0.0f, y, D}}, gridColor);
        drawLine3D(win, MathsVector<float, 3>{{0.0f, 0.0f, z}}, MathsVector<float, 3>{{0.0f, H, z}}, gridColor);

        drawLine3D(win, MathsVector<float, 3>{{W, y, 0.0f}}, MathsVector<float, 3>{{W, y, D}}, gridColor);
        drawLine3D(win, MathsVector<float, 3>{{W, 0.0f, z}}, MathsVector<float, 3>{{W, H, z}}, gridColor);
    }
}



void View3D::drawBoid(sf::RenderWindow& win, const MathsVector<float, 3>& position,const MathsVector<float, 3>& direction, Species::BoidSpecies BoidSpecie) {
    const float length{18.0f};
    const float width{6.0f};
    const float height{6.0f};

    MathsVector<float, 3> forward{direction.normalized()};
    MathsVector<float, 3> worldUp{(std::abs(forward[1]) > 0.99f) ? MathsVector<float, 3>{{1.0f, 0.0f, 0.0f}} : MathsVector<float, 3>{{0.0f, 1.0f, 0.0f}}};
    MathsVector<float, 3> right{worldUp.cross(forward).normalized()};
    MathsVector<float, 3> up{forward.cross(right)};

    // Piramide description ( top vertical then base verticals )
    std::vector<MathsVector<float, 3>> local{{
        MathsVector<float, 3>{{ 0.0f, 0.0f, length }},
        MathsVector<float, 3>{{-width, -height, 0.0f}},
        MathsVector<float, 3>{{ width, -height, 0.0f}},
        MathsVector<float, 3>{{ width, height, 0.0f}},
        MathsVector<float, 3>{{-width, height, 0.0f}}
    }};

    std::vector<MathsVector<float, 3>> world(local.size());
    for (size_t i = 0; i < local.size(); ++i) {
        world[i] = position + right * local[i][0] + up * local[i][1] + forward * local[i][2];
    }

    static constexpr Face faces[] = {
        {0,1,2},
        {0,2,3},
        {0,3,4},
        {0,4,1}
    };

    if(BoidSpecie == Species::BoidSpecies::CYAN) 
        for (const Face& f : faces)
            drawTriangle3D(win, world[f.a], world[f.b], world[f.c], sf::Color::Cyan);
            
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


void View3D::drawObstacle(sf::RenderWindow& win, const MathsVector<float, 3>& position, int sizeX, int sizeY, int sizeZ) {
    const float width{static_cast<float>(sizeX)};
    const float height{static_cast<float>(sizeY)};
    const float Depth{static_cast<float>(sizeZ)};

    // Cube description
    std::vector<MathsVector<float, 3>> local{{
        MathsVector<float, 3>{{-width, -height, -Depth}} / 2.0f,
        MathsVector<float, 3>{{ width, -height, -Depth}} / 2.0f,
        MathsVector<float, 3>{{ width, -height, Depth}} / 2.0f,
        MathsVector<float, 3>{{-width, -height, Depth}} / 2.0f,
        MathsVector<float, 3>{{-width, height, -Depth}} / 2.0f,
        MathsVector<float, 3>{{ width, height, -Depth}} / 2.0f,
        MathsVector<float, 3>{{ width, height, Depth}} / 2.0f,
        MathsVector<float, 3>{{-width, height, Depth}} / 2.0f,
    }};

    std::vector<MathsVector<float, 3>> world(local.size());
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
