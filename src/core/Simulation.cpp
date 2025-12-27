#include "../include/Simulation.hpp"
#include "../include/config/Settings.hpp"
#include <cstdlib>

namespace bd {

Simulation::Simulation() : window(sf::VideoMode(1200, 600), "Boids Simulation") {
    window.setFramerateLimit(60);

    leftView.setSize(settings.windowWidth, settings.windowHeight);
    leftView.setCenter(settings.windowWidth / 2.f, settings.windowHeight / 2.f);

    rightView.setSize(settings.windowSetWidth, settings.windowSetHeight);
    rightView.setCenter(settings.windowSetWidth / 2.f, settings.windowSetHeight / 2.f);


    for (int i = 0; i < 50; ++i) {
        flock.addBoid(Boid(rand() % 800, rand() % 600));
    }

    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());
}

// Tempo
void Simulation::drawPanel() {
    sf::RectangleShape bg({400.f, 600.f});
    bg.setFillColor(sf::Color(30, 30, 30));
    bg.setPosition(0, 0);
    window.draw(bg);
}


void Simulation::run() {
    while (window.isOpen()) {
        controller.handleInput(flock, window);
        flock.update();

        window.clear(sf::Color::Black);

        window.setView(leftView);
        view.draw(window, flock);

        window.setView(rightView);
        drawPanel();

        window.display();
    }
}


}
