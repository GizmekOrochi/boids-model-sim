#include "../../include/controller/Controller.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace bd {

// TODO: DEGAGER LE POLLING (still true; later we can move event polling to Application)

void Controller::handleInput(Simulation& simulation, sf::RenderWindow& window) {
    Flock& flock = simulation.getFlock();
    Settings& s = flock.getSettings();

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        // --- Save/Load (event-based, single trigger) ---
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::S) {
                if (!SaveSystem::save(simulation, "save.boids"))
                    std::cerr << "Save failed\n";
                else
                    std::cerr << "Saved to save.boids\n";
            }

            if (event.key.code == sf::Keyboard::L) {
                if (!SaveSystem::load(simulation, "save.boids"))
                    std::cerr << "Load failed\n";
                else
                    std::cerr << "Loaded from save.boids\n";
            }
        }
    }

    // --- Adjust perception radius (real-time hold) ---
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) s.perceptionRadius += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) s.perceptionRadius -= 1;

    // --- Adjust separation distance (real-time hold) ---
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) s.separationDistance += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) s.separationDistance -= 1;

    // --- Safely adjust rule weights (real-time hold) ---
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

    // --- Min bounds ---
    if (s.perceptionRadius < 5) s.perceptionRadius = 5;
    if (s.separationDistance < 5) s.separationDistance = 5;
}

}
