#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include "model/Flock.hpp"
#include "view/View.hpp"
#include "controller/Controller.hpp"

namespace bd {

class Simulation {
private:
    sf::RenderWindow window;
    Flock flock;
    View view;
    Controller controller;

public:
    Simulation();
    void run();
};

}

#endif
