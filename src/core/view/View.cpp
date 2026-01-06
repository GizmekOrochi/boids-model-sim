#include "../../include/view/View.hpp"
#include <iostream>
#include <sstream>

namespace bd {

View::View(sf::Font& f, int w, int h) : font(f) , view3D(w, h), viewlayout() {}

Camera& View::getCamera() {
    return view3D.getCamera();
}

void View::setViewport(int w, int h) {
    view3D.setViewport(w, h);
}

void View::drawPanel(sf::RenderWindow& win, float w) {
    sf::RectangleShape bg({w, (float)win.getSize().y});
    bg.setFillColor(sf::Color(50,50,50));
    win.draw(bg);
}

void View::drawUI(sf::RenderWindow& win, const std::vector<Button>& buttons, const std::vector<Slider>& sliders) {
    for (const auto& b : buttons) {
        sf::RectangleShape r(b.size);
        r.setPosition(b.pos);
        r.setFillColor(b.hovered ? sf::Color(100,100,100) : sf::Color(70,70,70));
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
        std::ostringstream ss;
        ss.setf(std::ios::fixed);
        ss.precision(3);
        ss << s.label << ": " << *s.valueRef;

        sf::Text t(ss.str(), font, 14);
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

void View::draw(sf::RenderWindow& win, float panelWidth) {
    view3D.drawWorldCage(win);
    // UI overlay
    drawPanel(win, panelWidth);
    viewlayout.build();
    drawUI(win, viewlayout.buttons, viewlayout.sliders);
}

}