#ifndef VIEW3D_HPP
#define VIEW3D_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include "../model/utils/MathsVector.hpp"
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

    MathsVector<float, 3> worldToCamera(const MathsVector<float, 3>& position) const;
    bool projectToScreen(const MathsVector<float, 3>& camP, MathsVector<float, 2>& out, float& outZ) const;

    void drawBoid(sf::RenderWindow& win, const MathsVector<float, 3>& position, const MathsVector<float, 3>& direction, Species::BoidSpecies BoidSpecie);
    void drawObstacle(sf::RenderWindow& win, const MathsVector<float, 3>& position, int sizeX, int sizeY, int sizeZ);
    void drawWorldCage(sf::RenderWindow& win);


private:
    Camera camera;
    int width;
    int height;


    float fovPixels = 520.f;
    float nearZ = 0.1f;

    void drawLine3D(sf::RenderWindow& win, const MathsVector<float, 3>& a, const MathsVector<float, 3>& b, sf::Color color);
    void drawTriangle3D(sf::RenderWindow& win, const MathsVector<float, 3>& a, const MathsVector<float, 3>& b, const MathsVector<float, 3>& c,sf::Color color);

};

}

#endif