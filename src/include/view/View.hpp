#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "utils/ui_types.hpp"
#include "View3D.hpp"
#include "ViewLayout.hpp"


namespace bd {

class View {
private:
    sf::Font& font;
    View3D view3D;
    ViewLayout viewlayout;
public:

    View(sf::Font& font, int w, int h);

    Camera& getCamera();

    View3D getView3D() { return view3D;}

    std::vector<Button>& getButtons() { return viewlayout.buttons; };
    std::vector<Slider>& getSliders() { return viewlayout.sliders; };


    void drawUI(sf::RenderWindow& win, const std::vector<Button>& buttons, const std::vector<Slider>& sliders);
    void draw(sf::RenderWindow& win);
    void setViewport(int w, int h);
};

}

#endif