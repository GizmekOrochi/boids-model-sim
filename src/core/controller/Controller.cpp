#include "../../include/controller/Controller.hpp"

#include "../../include/model/utils/SaveSystem.hpp"
#include "../../include/model/Boids_rules/Cohesion.hpp"
#include "../../include/model/Boids_rules/Separation.hpp"
#include "../../include/model/Boids_rules/Alignment.hpp"

#include <cstdlib>
#include <iostream>

namespace bd {

Controller::Controller(const Settings& settings) : simulation(World(settings.windowWidth, settings.windowHeight), settings.deltaTime), renderer(font) {
    if (!font.loadFromFile("assets/font/arial.ttf")) {
        std::cerr << "ERROR: failed to load font\n";
    }

    simulation.getFlock().getSettings() = settings;
}

void Controller::run() {
    auto& flock = simulation.getFlock();
    Settings& s = flock.getSettings();

    layout.build(s);

    float panelWidth = layout.panelWidth;
    float worldW = simulation.getWorld().getWidth();
    float worldH = simulation.getWorld().getHeight();

    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());

    window.create(sf::VideoMode(static_cast<unsigned>(worldW + panelWidth), static_cast<unsigned>(worldH)), "Boids Simulation");
    window.setFramerateLimit(60);

    for (int i = 0; i < s.nbboid; ++i) {
        float x = rand() / float(RAND_MAX) * worldW;
        float y = rand() / float(RAND_MAX) * worldH;
        flock.addBoid(Boid(static_cast<float>(x), static_cast<float>(y)));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            UiAction action = control.handleEvent(
                event, window, layout.buttons, layout.sliders
            );

            switch (action) {
                case UiAction::Save:
                    SaveSystem::save(simulation, "save.boids");
                    break;
                case UiAction::Load:
                    SaveSystem::load(simulation, "save.boids");
                    break;
                case UiAction::AddBoid:
                    flock.addBoid(Boid(worldW * 0.5f, worldH * 0.5f));
                    break;
                case UiAction::RmBoid:
                    flock.removeLastBoid();
                    break;
                default:
                    break;
            }
        }

        control.update(window, layout.buttons, layout.sliders);
        simulation.update();

        window.clear(sf::Color::Black);
        renderer.drawPanel(window, panelWidth);
        renderer.drawUI(window, layout.buttons, layout.sliders);
        renderer.drawBoids(window, flock, panelWidth);
        window.display();
    }
}

}
