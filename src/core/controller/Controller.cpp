#include "../../include/controller/Controller.hpp"

#include <iostream>
#include <cstdlib>

namespace bd {

Controller::Controller() : simulation(settings::deltaTime) , view(font, settings::windowWidth, settings::windowHeight) {
    if (!font.loadFromFile("assets/font/arial.ttf")) {
        std::cerr << "ERROR: failed to load font\n";
    }
}

void Controller::run() {
    auto& flock = simulation.getFlock();

    view.initWorld(window);

    const float panelWidth = settings::panelWidth;
    const float worldW = simulation.getWorld().getWidth();
    const float worldH = simulation.getWorld().getHeight();

    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());

    window.create(sf::VideoMode(static_cast<unsigned>(worldW + panelWidth),static_cast<unsigned>(worldH)),"Boids Simulation");
    window.setFramerateLimit(60);

    for (int i = 0; i < settings::nbboid; ++i) {
        float x = rand() / float(RAND_MAX) * worldW;
        float y = rand() / float(RAND_MAX) * worldH;
        float z = rand() / float(RAND_MAX) * settings::windowDeepth;
        flock.addBoid(Boid(x, y, z));
    }

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                view.setViewport(event.size.width, event.size.height);
            }

            UiAction action = viewControl.handleEvent(event, window, view.getButtons(),view.getSliders());

            switch (action) {
                case UiAction::Save:
                    SaveSystem::save(simulation, "save.boids");
                    break;

                case UiAction::Load:
                    SaveSystem::load(simulation, "save.boids");
                    break;

                case UiAction::AddBoid:
                    flock.addBoid(Boid(worldW * 0.5f, worldH * 0.5f, 0.f));
                    break;

                case UiAction::RmBoid:
                    flock.removeLastBoid();
                    break;

                default:
                    break;
            }
        }

        // --- Continuous input ---
        viewControl.updateCamera(view.getCamera(), dt);
        viewControl.update(window, view.getButtons(), view.getSliders());

        // --- Simulation ---
        simulation.update();

        // --- Render ---
        window.clear(sf::Color(15, 15, 20));

        view.drawPanel(window, panelWidth);
        view.drawUI(window, view.getButtons(), view.getSliders());

        view.getView3D().drawWorldCage(window);

        const auto& boids = flock.getBoids();
        for (size_t i = 0; i < boids.getsize(); ++i) {
            const Boid& b = boids[i];
            if (b.velocity.lengthSq() < 1e-6f) continue;

            view.getView3D().drawBoid(
                window,
                b.position,
                b.velocity
            );
        }

        window.display();
    }
}

}
