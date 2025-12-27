#ifndef CONTROLLERVIEW_HPP
#define CONTROLLERVIEW_HPP

#include <SFML/Graphics.hpp>
#include "../config/Settings.hpp"

namespace bd {

class ControllerView {
public:
    explicit ControllerView(const Settings& settings);
    void draw(sf::RenderWindow& window);

private:
    const Settings& settings;
    sf::Font font;
    sf::Text text;
};

}

#endif
