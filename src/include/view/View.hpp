#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "ui_types.hpp"
#include "View3D.hpp"


namespace bd {

class View {
public:
    View(sf::Font& font, int w, int h);

    Camera& getCamera();
    View3D getView3D() { return view3D;}

    void initWorld(sf::RenderWindow& win);

    void drawPanel(sf::RenderWindow& win, float w);
    void draw(sf::RenderWindow& win, float panelWidth);

    void setViewport(int w, int h);

private:
    sf::Font& font;
    View3D view3D;
};

}

#endif

