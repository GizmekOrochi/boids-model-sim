#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "../model/Flock.hpp"

namespace bd {

class View {
private:
    sf::Font font;
    sf::Text uiText;

public:
    View();

    void draw(sf::RenderWindow& window, const Flock& flock);
};

}

#endif
