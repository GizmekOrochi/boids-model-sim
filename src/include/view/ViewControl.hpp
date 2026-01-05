#ifndef VIEW_CONTROL_HPP
#define VIEW_CONTROL_HPP

#include <SFML/Graphics.hpp>
#include "ui_types.hpp"
#include "utils/Camera.hpp"

namespace bd {

class ViewControl {
public:
    UiAction handleEvent(const sf::Event& event,const sf::RenderWindow& window,std::vector<Button>& buttons,std::vector<Slider>& sliders);
    void update(const sf::RenderWindow& window, std::vector<Button>& buttons, std::vector<Slider>& sliders);
    void updateCamera(Camera& cam, float dt);
};

}

#endif
