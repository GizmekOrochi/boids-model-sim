#include "../../include/model/Simulation.hpp"

namespace bd {

Simulation::Simulation(float dt) : world(), deltaTime(dt), eaten(nullptr) { 
    eaten = new DynamicArray<int>();
    init(); 
}

void Simulation::init() {
    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());
    flock.addRule(new Avoidance());
    flock.addRule(new Death());
}

void Simulation::update() {
    auto& boids = flock.getBoids();
    auto nextVel = flock.computeNextVelocities(eaten);

    for (size_t i = 0; i < boids.getsize(); ++i) {
        boids[i].velocity = nextVel[i];
        boids[i].position += boids[i].velocity * deltaTime;
        world.handleBoundaries(boids[i]);
        removeEatenBoids(boids, *eaten);
    }
    settings::nbboid = flock.getBoids().getsize();
}

void Simulation::removeEatenBoids(DynamicArray<Boid>& boids, const DynamicArray<int>& eaten) {
    for (int i = boids.getsize() - 1; i >= 0; --i) {
        for (size_t j = 0; j < eaten.getsize(); ++j) {
            if (boids[i].ID == eaten[j]) {
                boids.erase(i);
                break;
            }
        }
    }
}

}
