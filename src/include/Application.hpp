#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

#include "model/Simulation.hpp"
#include "view/View.hpp"
#include "controller/Controller.hpp"
#include "config/Settings.hpp"

namespace bd {

/**
 * @brief Entry point of the application layer.
 *
 * The Application class owns and coordinates the high-level components
 * of the program, including the window, simulation, view, and controller.
 * It is responsible for initializing the application and running the
 * main loop that drives input handling, simulation updates, and rendering.
 */
class Application {
private:
    /** Render window used for displaying the simulation. */
    sf::RenderWindow window;

    /** Core simulation model containing world and flock state. */
    Simulation simulation;

    /** View responsible for rendering the simulation state. */
    View view;

    /** Controller responsible for handling user input. */
    Controller controller;

public:
    /**
     * @brief Constructs the application with the given settings.
     *
     * Initializes the simulation and prepares the application
     * using the provided configuration parameters.
     *
     * @param settings Configuration values used to initialize the application.
     */
    explicit Application(const Settings& settings);

    /**
     * @brief Runs the main application loop.
     *
     * This function creates the window and continuously processes input,
     * updates the simulation, and renders the current state until the
     * application is terminated.
     */
    void run();
};

}

#endif // APPLICATION_HPP
