#include "../include/Simulation.hpp"
#include <cstdlib>

namespace bd {

Simulation::Simulation()
    : window(sf::VideoMode(800, 600), "Boids Simulation")
{
    window.setFramerateLimit(60);

    // Initialize boids
    for (int i = 0; i < 50; ++i) {
        float x = rand() % 800;
        float y = rand() % 600;
        flock.addBoid(Boid(x, y));
    }

    // Add default rules
    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());
}

void Simulation::run() {
    while (window.isOpen()) {
        controller.handleInput(flock, window);

        flock.update();

        window.clear(sf::Color::Black);
        view.draw(window, flock);
        window.display();
    }
}

}
