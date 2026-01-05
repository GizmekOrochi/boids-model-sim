#include "../../include/view/View.hpp"
#include <cmath>

namespace bd {

View::View(sf::Font& f) : font(f) {}

void View::drawPanel(sf::RenderWindow& win, float w) {
    sf::RectangleShape bg({w, (float)win.getSize().y});
    bg.setFillColor(sf::Color(50,50,50));
    win.draw(bg);
}

void View::drawUI(
    sf::RenderWindow& win,
    const std::vector<Button>& buttons,
    const std::vector<Slider>& sliders
) {
    for (const auto& b : buttons) {
        sf::RectangleShape r(b.size);
        r.setPosition(b.pos);
        r.setFillColor(b.hovered ? sf::Color(100,100,100)
                                 : sf::Color(70,70,70));
        r.setOutlineThickness(1);
        r.setOutlineColor(sf::Color::White);
        win.draw(r);

        sf::Text t(b.label, font, 14);
        auto tb = t.getLocalBounds();
        t.setOrigin(tb.left + tb.width/2, tb.top + tb.height/2);
        t.setPosition(b.pos.x + b.size.x/2, b.pos.y + b.size.y/2);
        win.draw(t);
    }

    for (const auto& s : sliders) {
        sf::Text t(s.label, font, 14);
        t.setPosition(s.position.x, s.position.y - 20);
        win.draw(t);

        sf::RectangleShape track({s.width, 10});
        track.setPosition(s.position);
        track.setFillColor(sf::Color(150,150,150));
        win.draw(track);

        float r = (*s.valueRef - s.minVal) / (s.maxVal - s.minVal);
        sf::RectangleShape knob({10,20});
        knob.setOrigin(5,10);
        knob.setPosition(s.position.x + r * s.width, s.position.y + 5);
        win.draw(knob);
    }
}

void View::drawBoids(
    sf::RenderWindow& win,
    const Flock& flock,
    float offset
) {
    const auto& boids = flock.getBoids();
    for (size_t i = 0; i < boids.getsize(); ++i) {
        const Boid& b = boids[i];

        sf::ConvexShape tri;
        tri.setPointCount(3);
        tri.setPoint(0, {0,-6});
        tri.setPoint(1, {12,0});
        tri.setPoint(2, {0,6});

        float ang = std::atan2(b.velocity.y, b.velocity.x) * 180.f / 3.14159f;
        tri.setRotation(ang);
        tri.setPosition(b.position.x + offset, b.position.y);

        win.draw(tri);
    }
}

}
