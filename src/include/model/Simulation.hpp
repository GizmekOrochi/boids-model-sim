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

class Simulation {
private:
    World world;
    Flock flock;

    float deltaTime;

    DynamicArray<int>* eaten;

    void init();

public:

    Simulation(float dt);

    ~Simulation() { delete eaten; };

    World& getWorld() { return world; }
    const World& getWorld() const { return world; }

    Flock& getFlock() { return flock; }
    const Flock& getFlock() const { return flock; }

    void update();

    void addBoid(const Boid& b) { flock.addBoid(b); }
    void addObstacle(const Obstacle& o) { flock.addObstacle(o); }

    void removeLastBoid() { flock.removeLastBoid(); }
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