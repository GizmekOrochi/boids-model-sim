#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Graphics.hpp>

#include "../model/Simulation.hpp"
#include "../model/utils/SaveSystem.hpp"
#include "../model/Boids_rules/Cohesion.hpp"
#include "../model/Boids_rules/Separation.hpp"
#include "../model/Boids_rules/Alignment.hpp"

namespace bd {

class Controller {
public:
    void handleInput(Simulation& simulation, sf::RenderWindow& window);
};

}

#endif
