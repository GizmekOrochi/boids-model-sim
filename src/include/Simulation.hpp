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

    sf::View leftView;
    sf::View rightView;

    Settings setting;
    
    Flock flock;
    View view;
    Controller controller;

public:
    Simulation();
    void drawPanel();
    void run();
};

}

#endif
