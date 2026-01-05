#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>

#include "../model/Simulation.hpp"
#include "../view/View.hpp"
#include "../view/ViewLayout.hpp"
#include "../view/ViewControl.hpp"
#include "../config/Settings.hpp"

namespace bd {

class Controller {
public:
    explicit Controller();
    void run();

private:
    Simulation simulation;

    sf::RenderWindow window;
    sf::Font font;

    ViewLayout layout;
    ViewControl control;
    View renderer;
};

}

#endif
