#include "../include/Simulation.hpp"
#include <cstdlib>

namespace bd {

Simulation::Simulation()
    : window(sf::VideoMode(settings.fullwindowWidth, settings.fullwindowHeight), "Boids Simulation"),
      controllerView(settings)
{
    window.setFramerateLimit(60);

    // LEFT VIEW (boids)
    leftView.setSize(settings.windowWidth, settings.windowHeight);
    leftView.setCenter(settings.windowWidth / 2.f, settings.windowHeight / 2.f);
    leftView.setViewport({0.f, 0.f, 0.66f, 1.f});

    // RIGHT VIEW (controller UI)
    rightView.setSize(settings.windowSetWidth, settings.windowSetHeight);
    rightView.setCenter(settings.windowSetWidth / 2.f, settings.windowSetHeight / 2.f);
    rightView.setViewport({0.66f, 0.f, 0.34f, 1.f});

    for (int i = 0; i < 50; ++i) {
        flock.addBoid(Boid(rand() % settings.windowWidth, rand() % settings.windowHeight));
    }

    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());
}

void Simulation::run() {
    while (window.isOpen()) {
        controller.handleInput(flock, window);
        flock.update();

        window.clear(sf::Color::Black);

        window.setView(leftView);
        view.draw(window, flock);

        window.setView(rightView);
        controllerView.draw(window);

        window.display();
    }
}

}
