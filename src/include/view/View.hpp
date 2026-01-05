#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "ui_types.hpp"
#include "../model/Flock.hpp"

namespace bd {

class View {
public:
    explicit View(sf::Font& font);

    void drawPanel(sf::RenderWindow& win, float panelWidth);
    void drawUI(sf::RenderWindow& win, const std::vector<Button>& buttons, const std::vector<Slider>& sliders);

    void drawBoids(sf::RenderWindow& win, const Flock& flock, float panelWidth);

private:
    sf::Font& font;
};

}

#endif
