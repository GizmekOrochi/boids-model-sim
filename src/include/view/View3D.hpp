#ifndef VIEW3D_HPP
#define VIEW3D_HPP

#include <SFML/Graphics.hpp>
#include "../model/utils/Vec2.hpp"
#include "../model/utils/Vec3.hpp"
#include "../model/utils/Species.hpp"
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

private:
    Camera camera;
    int width;
    int height;

    float fovPixels = 520.f;
    float nearZ = 0.1f;

    void drawLine3D(sf::RenderWindow& win, const Vec3<float>& a, const Vec3<float>& b, sf::Color color);
    void drawTriangle3D(sf::RenderWindow& win, const Vec3<float>& a, const Vec3<float>& b, const Vec3<float>& c,sf::Color color);

    Vec3<float> worldToCamera(const Vec3<float>& p) const;
    bool projectToScreen(const Vec3<float>& camP, Vec2<float>& out, float& outZ) const;

    void drawBoid(sf::RenderWindow& win, const Vec3<float>& position, const Vec3<float>& direction, Species::BoidSpecies BoidSpecie);
    void drawObstacle(sf::RenderWindow& win, const Vec3<float>& position, int sizeX, int sizeY, int sizeZ);
    void drawWorldCage(sf::RenderWindow& win);

};

}

#endif