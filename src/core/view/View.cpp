#include "../../include/view/View.hpp"

namespace bd {

View::View(sf::Font& f, int w, int h)
    : font(f)
    , view3D(w, h)
{}

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

void View::initWorld(sf::RenderWindow& win) {
    view3D.drawWorldCage(win);
}

void View::draw(sf::RenderWindow& win, float panelWidth) {
    // 3D first (world)
    view3D.draw(win);
    view3D.drawWorldCage(win);

    // UI overlay
    //drawPanel(win, panelWidth);
}

}