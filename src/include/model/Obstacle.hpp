#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#pragma once
#include <string>
#include "utils/Vec3.hpp"

namespace bd {


class Obstacle {
public:
    Vec3<float> position;

    int sizeX;
    int sizeY;
    int sizeZ;

    Obstacle() : position(0.0f,0.0f,0.0f), sizeX(10.0f), sizeY(10.0f), sizeZ(10.0f) {}
    Obstacle(float x, float y, float z, int sizeX, int sizeY, int sizeZ) : position(x,y,z), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {}
};

} //namespace


#endif // OBSTACLE_HPP