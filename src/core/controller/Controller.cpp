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
    const float panelWidth = settings::panelWidth;
    const float worldW = settings::windowWidth;
    const float worldH = settings::windowHeight;

    window.create(sf::VideoMode(static_cast<unsigned>(worldW + panelWidth),static_cast<unsigned>(worldH)),"Boids Simulation");
    window.setFramerateLimit(60);

    for (int i = 0; i < settings::nbboid; ++i) {
        spawnRandBoid();
    }

    for (int i = 0; i < settings::nbobstacle; ++i) {
        spawnRandObstacle();
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

                case UiAction::AddBoid:
                    if (simulation.getBoids().getsize() < 200) {
                        spawnRandBoid();
                    }
                    break;

                case UiAction::RmBoid:
                    if (simulation.getBoids().getsize() > 10) {
                        simulation.removeLastBoid();
                    }
                    break;
                case UiAction::AddObstacle:
                    spawnRandObstacle();
                    break;

                case UiAction::RmObstacle:
                    simulation.removeLastObstacle();
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

        const auto& boids = simulation.getBoids();

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

        const auto& obs = simulation.getObstacles();

        for (size_t i = 0; i < obs.getsize(); ++i) {
            const Obstacle b = obs[i];

            Vec3<float> camP = view.getView3D().worldToCamera(b.position);
            Vec2<float> screen;
            float z;

            if (view.getView3D().projectToScreen(camP, screen, z)) {
                if (screen.x >= panelWidth) {
                    view.getView3D().drawObstacle(window, b.position, b.sizeX, b.sizeY, b.sizeY);
                }
            }
        }


        view.draw(window, panelWidth);
        
        window.display();
    }
}

void Controller::spawnRandBoid() {
    // race
    int r = (rand() % 3);
    BoidSpecies species = (r == 0) ? BoidSpecies::RED : (r == 1) ? BoidSpecies::GREEN : BoidSpecies::BLUE;

    // location
    constexpr float SPAWN_RADIUS = 100.0f;
    float cx = settings::worldWidth * 0.5f;
    float cy = settings::worldHeight * 0.5f;
    float cz = settings::worldDeepth * 0.5f;

    simulation.addBoid(Boid(
        cx + randRange(-SPAWN_RADIUS, SPAWN_RADIUS),
        cy + randRange(-SPAWN_RADIUS, SPAWN_RADIUS),
        cz + randRange(-SPAWN_RADIUS, SPAWN_RADIUS),
        species
    ));
}

void Controller::spawnRandObstacle() {
    // Randowm obstacle size
    float obsW = randRange(20, 100); // X size
    float obsH = randRange(20, 100); // Y size
    float obsD = randRange(20, 100); // Z size

    simulation.addObstacle(Obstacle(
        randRange(0.0f + obsW, settings::worldWidth - obsW),
        randRange(0.0f + obsH, settings::windowWidth - obsH),
        randRange(0.0f + obsD, settings::worldDeepth - obsD), 
        static_cast<int>(obsW),
        static_cast<int>(obsH),
        static_cast<int>(obsD)
    ));
}
 
float Controller::randRange(float min, float max){
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min);
}

}
