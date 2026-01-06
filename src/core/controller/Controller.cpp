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

    const float panelWidth = settings::panelWidth;
    const float worldW = simulation.getWorld().getWidth();
    const float worldH = simulation.getWorld().getHeight();

    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());
    flock.addRule(new Avoidance());

    window.create(sf::VideoMode(static_cast<unsigned>(worldW + panelWidth),static_cast<unsigned>(worldH)),"Boids Simulation");
    window.setFramerateLimit(60);

    for (int i = 0; i < settings::nbboid; ++i) {
        float x = rand() / float(RAND_MAX) * settings::worldWidth;
        float y = rand() / float(RAND_MAX) * settings::worldHeight;
        float z = rand() / float(RAND_MAX) * settings::worldDeepth;

        int r = (rand() % 3) + 1;
        if(r == 1) { flock.addBoid(Boid(x, y, z, BoidSpecies::RED)); }
        if(r == 2) { flock.addBoid(Boid(x, y, z, BoidSpecies::GREEN)); }
        else { flock.addBoid(Boid(x, y, z, BoidSpecies::BLUE)); }
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
                    SaveSystem::save(simulation, "bin/save.boids");
                    break;

                case UiAction::Load:
                    SaveSystem::load(simulation, "bin/save.boids");
                    break;

                case UiAction::AddBoid: {
                    if (settings::nbboid < 200) {
                        int r = (rand() % 3) + 1;
                        if(r == 1) { flock.addBoid(Boid(worldW * 0.5f, worldH * 0.5f, 0.f, BoidSpecies::RED)); settings::nbboid++;}
                        if(r == 2) { flock.addBoid(Boid(worldW * 0.5f, worldH * 0.5f, 0.f, BoidSpecies::GREEN)); settings::nbboid++;}
                        else { flock.addBoid(Boid(worldW * 0.5f, worldH * 0.5f, 0.f, BoidSpecies::BLUE)); settings::nbboid++;}

                    }
                    break;
                }

                case UiAction::RmBoid:
                    if (settings::nbboid > 10) {
                        flock.removeLastBoid();
                        settings::nbboid--;
                    }
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
        
        const auto& boids = flock.getBoids();
        for (size_t i = 0; i < boids.getsize(); ++i) {
            const Boid& b = boids[i];
            if (b.velocity.lengthSq() < 1e-6f) continue;
            Vec3<float> camP = view.getView3D().worldToCamera(b.position);
            Vec2<float> screen;
            float z;

            if (view.getView3D().projectToScreen(camP, screen, z)) {
                if (screen.x >= panelWidth) {
                    view.getView3D().drawBoid(window, b.position, b.velocity, b.specie);
                }
            }
        }

        view.draw(window, panelWidth);
        
        window.display();
    }
}

}
