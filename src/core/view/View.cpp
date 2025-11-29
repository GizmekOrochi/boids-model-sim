#include "../../include/view/View.hpp"
#include <cmath>

namespace bd {

View::View() {
    font.loadFromFile("arial.ttf"); // Make sure you include this file
    uiText.setFont(font);
    uiText.setCharacterSize(14);
    uiText.setFillColor(sf::Color::White);
}

void View::draw(sf::RenderWindow& window, const Flock& flock) {
    const auto& boids = flock.getBoids();
    const Settings& s = flock.getSettings();

    // --- Draw each boid ---
    for (size_t i = 0; i < boids.getsize(); ++i) {
        const Boid& b = boids[i];

        // oriented triangle
        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(0, -6));
        triangle.setPoint(1, sf::Vector2f(12, 0));
        triangle.setPoint(2, sf::Vector2f(0, 6));
        triangle.setFillColor(sf::Color::White);

        float angle = std::atan2(b.velocity.y, b.velocity.x) * 180.f / 3.14159f;
        triangle.setRotation(angle);
        triangle.setPosition(b.position.x, b.position.y);

        window.draw(triangle);
    }

    // --- Draw UI parameters ---
    std::string text;
    text += "Perception radius (R/F): " + std::to_string(s.perceptionRadius) + "\n";
    text += "Separation dist (T/G):  " + std::to_string(s.separationDistance) + "\n";

    uiText.setString(text);
    uiText.setPosition(10, 10);
    window.draw(uiText);
}

}
