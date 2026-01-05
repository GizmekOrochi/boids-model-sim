#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "utils/Vec2.hpp"
#include "utils/Vec3.hpp"
#include "utils/Camera.hpp"

namespace bd {

struct Face {
    // indices into vertex list (triangles)
    int a, b, c;
};

class Renderer3D {
public:
    Renderer3D(int w, int h)
        : width(w), height(h) {}

    Camera& getCamera() { return camera; }

    void setViewport(int w, int h) { width = w; height = h; }

    // Draw a filled + wireframe pyramid in world space
    void drawPyramid(sf::RenderWindow& win);

private:
    int width = 800;
    int height = 600;

    Camera camera;

    // Projection parameters
    float fovPixels = 520.f; // tweak: larger = narrower FOV
    float nearZ = 0.1f;

    // transform world point to camera space (view space)
    Vec3<float> worldToCamera(const Vec3<float>& p) const;

    // project camera-space point to screen; returns (x,y) and also outputs depth z
    bool projectToScreen(const Vec3<float>& camP, Vec2<float>& out, float& outZ) const;
};

} // namespace bd
