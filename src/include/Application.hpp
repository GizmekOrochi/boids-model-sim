#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

#include "model/Simulation.hpp"
#include "view/View.hpp"
#include "controller/Controller.hpp"
#include "config/Settings.hpp"

namespace bd {

class Application {
private:
    sf::RenderWindow window;

    Simulation simulation;
    View view;
    Controller controller;

public:
    explicit Application(const Settings& settings);
    void run();
};

}

#endif // APPLICATION_HPP
