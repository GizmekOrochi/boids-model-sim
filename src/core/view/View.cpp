#include "../../include/view/View.hpp"
#include <cmath>

namespace bd {

View::View() {}

void View::draw(sf::RenderWindow& window, const Flock& flock) {
    const auto& boids = flock.getBoids();

    for (size_t i = 0; i < boids.getsize(); ++i) {
        const Boid& b = boids[i];

        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, {0.f, -6.f});
        triangle.setPoint(1, {12.f, 0.f});
        triangle.setPoint(2, {0.f, 6.f});
        triangle.setFillColor(sf::Color::White);

        float angle =
            std::atan2(b.velocity.y, b.velocity.x) * 180.f / 3.14159265f;

        triangle.setRotation(angle);
        triangle.setPosition(b.position.x, b.position.y);

        window.draw(triangle);
    }
}


}
