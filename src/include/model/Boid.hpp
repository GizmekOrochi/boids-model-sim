#ifndef BOID_HPP
#define BOID_HPP

#pragma once
#include "utils/Vec3.hpp"
#include "utils/Species.hpp"
#include "../config/Settings.hpp"

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
    Vec3<float> position;

    /** Current velocity of the boid. */
    Vec3<float> velocity;

    /** Current specie of the boid */
    Species::BoidSpecies specie;

    /** ID of the boid */
    int ID;

    /**
     * @brief Constructs a boid at the origin with zero velocity.
     */
    Boid(Species::BoidSpecies specie) : position(0.0f,0.0f,0.0f), velocity(0.0f,0.0f,0.0f), specie(specie), ID(settings::currentIDAvalible) {
        settings::currentIDAvalible++;
    }

    /**
     * @brief Constructs a boid at a given position with zero velocity.
     *
     * @param x Initial x-coordinate.
     * @param y Initial y-coordinate.
     */
    Boid(float x, float y, float z, Species::BoidSpecies specie) : position(x,y,z), velocity(0.0f,0.0f,0.0f), specie(specie), ID(settings::currentIDAvalible) {
        settings::currentIDAvalible++;
    }

    ~Boid() { settings::currentIDAvalible--; }
};

}

#endif // BOID_HPP
