#include "../../include/model/Simulation.hpp"

namespace bd {

Simulation::Simulation(float dt) : world(), deltaTime(dt) {}

void Simulation::update() {
    auto& boids = flock.getBoids();
    auto nextVel = flock.computeNextVelocities();

    for (size_t i = 0; i < boids.getsize(); ++i) {
        boids[i].velocity = nextVel[i];
        boids[i].position += boids[i].velocity * deltaTime;
        world.handleBoundaries(boids[i]);
    }
}

}
