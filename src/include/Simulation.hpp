#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include "model/Flock.hpp"
#include "view/View.hpp"
#include "view/ControllerView.hpp"
#include "controller/Controller.hpp"
#include "config/Settings.hpp"

namespace bd {

class Simulation {
private:
    sf::RenderWindow window;

    sf::View leftView;
    sf::View rightView;

    Settings settings;

    Flock flock;
    View view;
    Controller controller;
    ControllerView controllerView;

public:
    Simulation();
    void run();
};

}

#endif
