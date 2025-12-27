#include "../include/Simulation.hpp"
#include <cstdlib>

namespace bd {

Simulation::Simulation() {}


void Simulation::run(Settings& settings) {
    window.create(sf::VideoMode(settings.windowWidth, settings.windowHeight),"Boids Simulation");
    window.setFramerateLimit(60);
    
    // Initialize boids only
    for (int i = 0; i < 50; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * settings.windowWidth;
        float y = static_cast<float>(rand()) / RAND_MAX * settings.windowHeight;
        flock.addBoid(Boid(x, y));
    }

    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());

    while (window.isOpen()) {
        controller.handleInput(flock, window);
        flock.update();

        window.clear(sf::Color::Black);
        view.draw(window, flock);
        window.display();
    }
}

}
