#include "../../include/view/ControllerView.hpp"
#include <stdexcept>

namespace bd {

ControllerView::ControllerView(const Settings& settings)
    : settings(settings)
{
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load UI font");
    }

    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
}

void ControllerView::draw(sf::RenderWindow& window) {
    sf::RectangleShape bg({400.f, 600.f});
    bg.setFillColor(sf::Color(30, 30, 30));
    window.draw(bg);

    std::string ui;
    ui += "Perception radius: " + std::to_string(settings.perceptionRadius) + "\n";
    ui += "Separation dist:   " + std::to_string(settings.separationDistance) + "\n";
    ui += "Cohesion weight:   " + std::to_string(settings.cohesionweight) + "\n";
    ui += "Alignment weight:  " + std::to_string(settings.alignmentweight) + "\n";

    text.setString(ui);
    text.setPosition(10.f, 10.f);
    window.draw(text);
}

}
