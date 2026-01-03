#ifndef BOID_HPP
#define BOID_HPP

#pragma once
#include "utils/Vec2.hpp"

namespace bd {

/**
 * @brief Represents a single boid in the simulation.
 *
 * A Boid encapsulates the minimal physical state required by the
 * simulation: its position in space and its velocity vector.
 * Behavioral rules operate on these values to produce flocking motion.
 */
class Boid {
public:
    /** Current position of the boid in world space. */
    Vec2<float> position;

    /** Current velocity of the boid. */
    Vec2<float> velocity;

    /**
     * @brief Constructs a boid at the origin with zero velocity.
     */
    Boid() : position(0,0), velocity(0,0) {}

    /**
     * @brief Constructs a boid at a given position with zero velocity.
     *
     * @param x Initial x-coordinate.
     * @param y Initial y-coordinate.
     */
    Boid(float x, float y) : position(x,y), velocity(0,0) {}
};

}

#endif // BOID_HPP
