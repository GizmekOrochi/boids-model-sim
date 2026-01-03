#include "../include/Application.hpp"
#include <cstdlib>

namespace bd {

Application::Application(const Settings& settings) : simulation( World(settings.windowWidth, settings.windowHeight), settings.deltaTime) {
    simulation.getFlock().getSettings() = settings;
}

void Application::run() {
    auto& flock = simulation.getFlock();

    window.create(
        sf::VideoMode(
            static_cast<unsigned int>(simulation.getWorld().getWidth()),
            static_cast<unsigned int>(simulation.getWorld().getHeight())
        ),
        "Boids Simulation"
    );

    window.setFramerateLimit(60);

    // Init boids
    for (int i = 0; i < 50; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * simulation.getWorld().getWidth();
        float y = static_cast<float>(rand()) / RAND_MAX * simulation.getWorld().getHeight();
        flock.addBoid(Boid(x, y));
    }

    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());

    while (window.isOpen()) {
        controller.handleInput(simulation, window);

        simulation.update();

        window.clear(sf::Color::Black);
        view.draw(window, flock);
        window.display();
    }
}

}
