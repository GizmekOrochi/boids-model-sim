#ifndef UI_TYPES_HPP
#define UI_TYPES_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace bd {

enum class UiAction {
    None,
    AddBoid,
    RmBoid,
    Save,
    Load,
    AddObstacle,
    RmObstacle,
    AddPredator
};


struct Slider {

    std::string label;
    float* valueRef;
    
    float minVal;
    float maxVal;
    sf::Vector2f position;
    float width;
    
    bool dragging = false;
};


struct Button {
    std::string label;
    UiAction action;
    sf::Vector2f pos;
    sf::Vector2f size;

    bool hovered = false;
};

}

#endif