#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#pragma once
#include "World.hpp"
#include "Flock.hpp"

namespace bd {

class Simulation {
private:
    World world;
    Flock flock;
    float deltaTime;

public:
    Simulation(const World& w, float dt);

    World& getWorld() { return world; }
    Flock& getFlock() { return flock; }

    const World& getWorld() const { return world; }
    const Flock& getFlock() const { return flock; }

    void update();
};


}

#endif // SIMULATION_HPP
