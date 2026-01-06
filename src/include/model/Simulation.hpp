#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#pragma once
#include "World.hpp"
#include "Flock.hpp"
#include "Obstacle.hpp"
#include "../model/Boids_rules/Cohesion.hpp"
#include "../model/Boids_rules/Separation.hpp"
#include "../model/Boids_rules/Alignment.hpp"
#include "../model/Boids_rules/Avoidance.hpp"
#include "../model/Boids_rules/Death.hpp"

namespace bd {

/**
 * @brief Coordinates the simulation of a flock within a world.
 *
 * The Simulation class owns both the World and the Flock and is
 * responsible for advancing the simulation state over time.
 * It serves as the central model component, orchestrating updates
 * without handling rendering or input concerns.
 */
class Simulation {
private:
    /** The world in which the simulation takes place. */
    World world;

    /** The flock being simulated within the world. */
    Flock flock;

    /** Time step used for advancing the simulation. */
    float deltaTime;

    DynamicArray<int>* eaten;

    /**
     * @brief Init the Flock
     */
    void init();

public:
    /**
     * @brief Constructs a simulation with a given world and time step.
     *
     * @param w The world instance defining spatial constraints.
     * @param dt The time delta used for each simulation update.
     */
    Simulation(float dt);

    /**
     * @brief Destruct a simulation.
     */
    ~Simulation() { delete eaten; };

    /**
     * @brief Provides mutable access to the world.
     *
     * @return Reference to the world.
     */
    World& getWorld() { return world; }

    /**
     * @brief Provides mutable access to the flock.
     *
     * @return Reference to the flock.
     */
    Flock& getFlock() { return flock; }

    /**
     * @brief Provides read-only access to the world.
     *
     * @return Const reference to the world.
     */
    const World& getWorld() const { return world; }

    /**
     * @brief Provides read-only access to the flock.
     *
     * @return Const reference to the flock.
     */
    const Flock& getFlock() const { return flock; }

    /**
     * @brief Advances the simulation by one time step.
     *
     * This function updates the flock state based on its rules
     * and applies world constraints using the configured delta time.
     */
    void update();


    // ALL thoses are accesser to the flock methodes from the controler
    void addBoid(const Boid& b) { flock.addBoid(b); }

    void removeLastBoid() { flock.removeLastBoid(); }

    void addObstacle(const Obstacle& o) { flock.addObstacle(o); }

    void removeLastObstacle() { flock.removeLastObstacle(); }

    void clearBoids() { flock.clearBoids(); }

    DynamicArray<Boid>& getBoids() { return flock.getBoids(); }

    DynamicArray<Obstacle>& getObstacles() { return flock.getObstacles(); }

    Boid& getBoid(size_t index) { return flock.getBoids()[index]; }

    size_t getBoidSize() { return flock.getBoids().getsize(); }

    void removeEatenBoids(DynamicArray<Boid>& boids, const DynamicArray<int>& eaten);
};

}

#endif // SIMULATION_HPP
