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

void ViewControl::updateCamera(Camera& cam, float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        cam.moveForward(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        cam.moveForward(-dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        cam.moveRight(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        cam.moveRight(-dt);

    // the speed factor is reversed because the y = 0 is the top of the world and y = 800 is the bottom 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        cam.moveUp(-dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        cam.moveUp(dt);

    float yawDelta = 0.0f;
    float pitchDelta = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        yawDelta -= 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        yawDelta += 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        pitchDelta += 1.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        pitchDelta -= 1.0f;

    if (yawDelta != 0.0f || pitchDelta != 0.0f)
        cam.rotate(yawDelta * dt, pitchDelta * dt);
}
}
