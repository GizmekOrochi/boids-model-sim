#include "../../include/view/ViewControl.hpp"
#include <algorithm>

namespace bd {

UiAction ViewControl::handleEvent(const sf::Event& e, const sf::RenderWindow& win, std::vector<Button>& buttons, std::vector<Slider>& sliders) {
    if (e.type == sf::Event::MouseButtonPressed) {
        auto m = sf::Mouse::getPosition(win);

        for (auto& s : sliders) {
            sf::FloatRect r(s.position.x, s.position.y - 10, s.width, 30);
            if (r.contains((float)m.x, (float)m.y))
                s.dragging = true;
        }

        for (auto& b : buttons) {
            if (sf::FloatRect(b.pos, b.size).contains((float)m.x, (float)m.y))
                return b.action;
        }
    }

    if (e.type == sf::Event::MouseButtonReleased) {
        for (auto& s : sliders){
            s.dragging = false;
        }
    }

    return UiAction::None;
}

void ViewControl::update(const sf::RenderWindow& win, std::vector<Button>& buttons, std::vector<Slider>& sliders) {
    auto m = sf::Mouse::getPosition(win);

    for (auto& s : sliders) {
        if (s.dragging) {
            float t = (m.x - s.position.x) / s.width;
            t = std::clamp(t, 0.f, 1.f);
            *s.valueRef = s.minVal + t * (s.maxVal - s.minVal);
        }
    }

    for (auto& b : buttons) { 
        b.hovered = sf::FloatRect(b.pos, b.size).contains((float)m.x, (float)m.y);
    }
}

}
