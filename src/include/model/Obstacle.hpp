#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#pragma once
#include <string>
#include "utils/Vec3.hpp"

namespace bd {

/**
 * @brief Represents a single boid in the simulation.
 *
 * A Obstacle is an being in the world that doesn't repsonde to any rule
 */
class Obstacle {
public:
    /** Current position of the Obstacle in world space. */
    Vec3<float> position;

    int sizeX;
    int sizeY;
    int sizeZ;

    /**
     * @brief Constructs a boid at the origin with zero velocity.
     */
    Obstacle() : position(0.0f,0.0f,0.0f), sizeX(10.0f), sizeY(10.0f), sizeZ(10.0f) {}

    /**
     * @brief Constructs a boid at a given position with zero velocity.
     *
     * @param x Initial x-coordinate.
     * @param y Initial y-coordinate.
     */
    Obstacle(float x, float y, float z, int sizeX, int sizeY, int sizeZ) : position(x,y,z), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {}
};

} //namespace


#endif // OBSTACLE_HPP