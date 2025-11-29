#include "../../include/controller/Controller.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace bd {

void Controller::handleInput(Flock& flock, sf::RenderWindow& window) {
    Settings& s = flock.getSettings();

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    // --- Adjust perception radius ---
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) s.perceptionRadius += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) s.perceptionRadius -= 1;

    // --- Adjust separation distance ---
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) s.separationDistance += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) s.separationDistance -= 1;

    // --- Safely adjust rule weights ---
    if (auto* c = flock.getRule<Cohesion>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) c->weight += 0.001f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) c->weight -= 0.001f;
    }
    if (auto* srule = flock.getRule<Separation>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) srule->weight += 0.001f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) srule->weight -= 0.001f;
    }
    if (auto* a = flock.getRule<Alignment>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) a->weight += 0.001f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) a->weight -= 0.001f;
    }

    // min bounds
    if (s.perceptionRadius < 5) s.perceptionRadius = 5;
    if (s.separationDistance < 5) s.separationDistance = 5;
}

}
