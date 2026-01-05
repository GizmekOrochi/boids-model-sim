#ifndef VIEW3D_HPP
#define VIEW3D_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../config/Settings.hpp"
#include "utils/Vec2.hpp"
#include "utils/Vec3.hpp"
#include "utils/Camera.hpp"

namespace bd {

struct Face {
    int a, b, c;
};

class View3D {
public:
    View3D(int w, int h);

    Camera& getCamera();

    void setViewport(int w, int h);
    void draw(sf::RenderWindow& win);

private:
    // ===== Camera & viewport =====
    Camera camera;
    int width;
    int height;

    // ===== Projection parameters =====
    float fovPixels = 520.f;
    float nearZ = 0.1f;

    // ===== Internal helpers =====
    Vec3<float> worldToCamera(const Vec3<float>& p) const;
    bool projectToScreen(
        const Vec3<float>& camP,
        Vec2<float>& out,
        float& outZ
    ) const;

    void drawLine3D(
        sf::RenderWindow& win,
        const Vec3<float>& a,
        const Vec3<float>& b,
        sf::Color color
    );

    public:

    void drawBoid(
        sf::RenderWindow& win,
        const Vec3<float>& position,
        const Vec3<float>& direction
    );

    void drawWorldCage(sf::RenderWindow& win);

};

}

#endif

