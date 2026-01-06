#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>

#include "../view/View.hpp"
#include "../view/ViewControl.hpp"
#include "../model/Simulation.hpp"
#include "../model/utils/SaveSystem.hpp"
#include "../model/utils/Species.hpp"
#include "../config/Settings.hpp"

namespace bd {

class Controller {
public:
    Controller();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;

    Simulation simulation;
    View view;
    ViewControl viewControl;

    float randRange(float min, float max);
    void spawnRandBoid();
};

}

#endif
