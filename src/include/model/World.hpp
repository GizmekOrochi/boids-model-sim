#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once
#include "Boid.hpp"

namespace bd {

/**
 * @brief Represents the spatial environment of the simulation.
 *
 * The World class defines the physical boundaries in which boids
 * exist and move. It is responsible for enforcing boundary behavior
 * such as reflection or containment when boids reach the edges
 * of the world.
 */
class World {
private:
    /** Width of the world space. */
    float width;

    /** Height of the world space. */
    float height;

public:
    /**
     * @brief Constructs a world with given dimensions.
     *
     * @param w Width of the world.
     * @param h Height of the world.
     */
    World(float w = 0.0f, float h = 0.0f);

    /**
     * @brief Returns the width of the world.
     *
     * @return World width.
     */
    float getWidth() const;

    /**
     * @brief Returns the height of the world.
     *
     * @return World height.
     */
    float getHeight() const;

    /**
     * @brief Handles boundary interactions for a boid.
     *
     * Adjusts the boid's position and velocity when it reaches
     * or exceeds the world boundaries.
     *
     * @param b The boid to process.
     */
    void handleBoundaries(Boid& b) const;
};

}

#endif // WORLD_HPP
