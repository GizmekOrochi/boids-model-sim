#ifndef VIEW_LAYOUT_HPP
#define VIEW_LAYOUT_HPP

#include <vector>
#include "utils/ui_types.hpp"
#include "../config/Settings.hpp"

namespace bd {

class ViewLayout {
    public:

        std::vector<Button> buttons;
        std::vector<Slider> sliders;

        void build();
    };

}

#endif