#include "../../include/view/ControllerView.hpp"
#include <stdexcept>

namespace bd {

ControllerView::ControllerView(const Settings& settings) : settings(settings) {}

void ControllerView::draw(sf::RenderWindow& window) {
    sf::RectangleShape bg({settings.windowSetWidth, settings.windowSetHeight});
    bg.setFillColor(sf::Color(30, 30, 30));
    window.draw(bg);
}

}
