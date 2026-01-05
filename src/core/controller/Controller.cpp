#include "../../include/controller/Controller.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

namespace bd {

Controller::Controller() : simulation(
        World(
            settings::windowWidth,
            settings::windowHeight,
            settings::windowDeepth
        ),
        settings::deltaTime
      )
    , view(font, settings::windowWidth, settings::windowHeight)
{
    if (!font.loadFromFile("assets/font/arial.ttf")) {
        std::cerr << "ERROR: failed to load font\n";
    }

    // === Attach rules ===
    Flock& flock = simulation.getFlock();
    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());

    // === Spawn 10 boids ===
    for (int i = 0; i < settings::nbboid; ++i) {
        float x = float(rand()) / RAND_MAX * settings::windowWidth;
        float y = float(rand()) / RAND_MAX * settings::windowHeight;
        float z = float(rand()) / RAND_MAX * settings::windowDeepth;

        flock.addBoid(Boid(x, y, z));
    }
}

void Controller::run() {
    constexpr int W = 800;
    constexpr int H = 600;
    const float panelWidth = settings::panelWidth;

    window.create(sf::VideoMode(W, H), "3D Boids");
    window.setFramerateLimit(60);

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                view.setViewport(
                    (int)event.size.width,
                    (int)event.size.height
                );
                sf::FloatRect area(
                    0, 0,
                    (float)event.size.width,
                    (float)event.size.height
                );
                window.setView(sf::View(area));
            }
        }

        // === Camera control (unchanged) ===
        Camera& cam = view.getCamera();
        float mv = cam.moveSpeed * dt;
        float rt = cam.rotSpeed  * dt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) cam.position += cam.forward() * mv;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cam.position -= cam.forward() * mv;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) cam.position -= cam.right()   * mv;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cam.position += cam.right()   * mv;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  cam.position += cam.up() * mv;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) cam.position -= cam.up() * mv;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  cam.yaw   -= rt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) cam.yaw   += rt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    cam.pitch += rt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  cam.pitch -= rt;

        cam.clampPitch();

        // === Update simulation ===
        simulation.update();

        // === Render ===
        window.clear(sf::Color(15,15,20));

        // draw world cage (already inside View3D::draw if you kept it)
        view.getView3D().drawWorldCage(window);

        // draw boids directly from simulation
        const auto& boids = simulation.getFlock().getBoids();

        for (size_t i = 0; i < boids.getsize(); ++i) {
            const Boid& b = boids[i];

            // avoid zero-direction boids
            if (b.velocity.lengthSq() < 1e-6f)
                continue;

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