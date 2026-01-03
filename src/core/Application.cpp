#include "../include/Application.hpp"
#include "../include/model/utils/SaveSystem.hpp"
#include <cstdlib>
#include <iostream>

namespace bd {

Application::Application(const Settings& settings)
    : simulation(World(settings.windowWidth, settings.windowHeight), settings.deltaTime) {
    simulation.getFlock().getSettings() = settings;
}

void Application::run() {
    auto& flock = simulation.getFlock();
    Settings& s = flock.getSettings(); // Référence vers les settings actifs

    // 1. Initialiser l'UI de la vue (création des sliders)
    view.initUI(s);

    // 2. Calcul des dimensions de la fenêtre
    // Largeur totale = Largeur Simulation + Largeur Menu (300px)
    float totalWidth = simulation.getWorld().getWidth() + view.getPanelWidth();
    float totalHeight = simulation.getWorld().getHeight();

    window.create(sf::VideoMode(static_cast<unsigned int>(totalWidth), static_cast<unsigned int>(totalHeight)), "Boids Simulation");
    window.setFramerateLimit(60);

    // Initialisation des boids
    for (int i = 0; i < 50; ++i) {
        float x = static_cast<float>(rand()) / RAND_MAX * simulation.getWorld().getWidth();
        float y = static_cast<float>(rand()) / RAND_MAX * simulation.getWorld().getHeight();
        flock.addBoid(Boid(x, y));
    }

    // Ajout des règles
    flock.addRule(new Cohesion());
    flock.addRule(new Separation());
    flock.addRule(new Alignment());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            controller.handleInput(simulation, window);

            // --- GESTION DES CLICS UI ---
            UiAction action = view.handleInput(event, window);

            // On réagit en fonction du bouton cliqué
            if (action == UiAction::Save) {
                std::cout << "Sauvegarde en cours..." << std::endl;
                if (!SaveSystem::save(simulation, "save.boids"))
                    std::cerr << "Echec de la sauvegarde" << std::endl;
                else
                    std::cout << "Sauvegarde reussie !" << std::endl;
            }
            else if (action == UiAction::Load) {
                std::cout << "Chargement en cours..." << std::endl;
                if (!SaveSystem::load(simulation, "save.boids"))
                    std::cerr << "Echec du chargement" << std::endl;
                else
                    std::cout << "Chargement reussi !" << std::endl;
            }
        }

        // Mise à jour de l'UI (Drag des sliders)
        view.updateUI(window);

        // IMPORTANT : Synchroniser les poids des règles
        // Les sliders modifient 's.cohesionweight', mais les objets Rule ont peut-être leur propre copie.
        // On met à jour les règles avec les nouvelles valeurs des Settings.
        if (auto* r = flock.getRule<Cohesion>())   r->weight = s.cohesionweight;
        if (auto* r = flock.getRule<Separation>()) r->weight = s.separationweight;
        if (auto* r = flock.getRule<Alignment>())  r->weight = s.alignmentweight;

        // Mise à jour simulation
        simulation.update();

        // Rendu
        window.clear(sf::Color::Black);

        // La vue dessine tout (Menu + Boids)
        view.draw(window, flock);

        window.display();
    }
}

}