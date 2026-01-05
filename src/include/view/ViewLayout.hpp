#ifndef VIEW_LAYOUT_HPP
#define VIEW_LAYOUT_HPP

#include <vector>
#include "ui_types.hpp"
#include "../config/Settings.hpp"

namespace bd {

class ViewLayout {
public:
    float panelWidth = 300.f;

    std::vector<Button> buttons;
    std::vector<Slider> sliders;

    void build(Settings& settings);
};

}

#endif
