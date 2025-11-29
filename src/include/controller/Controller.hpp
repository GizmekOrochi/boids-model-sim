#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../model/Flock.hpp"
#include "../model/Cohesion.hpp"
#include "../model/Separation.hpp"
#include "../model/Alignment.hpp"

namespace bd {

class Controller {
public:
    void handleInput(Flock& flock, sf::RenderWindow& window);
};

}

#endif
