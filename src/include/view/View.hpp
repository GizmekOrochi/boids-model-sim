#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../model/Flock.hpp"
#include "../config/Settings.hpp"

namespace bd {
    enum class UiAction {
        None,
        Save,
        Load
    };
    // Structure interne pour un slider
    struct Slider {
        std::string label;
        float* valueRef; // Pointeur direct vers la variable du Settings
        float minVal;
        float maxVal;
        sf::Vector2f position;
        float width;
        float height;
        bool isDragging;
    };

    // Nouvelle structure pour les boutons
    struct Button {
        std::string label;
        UiAction action; // L'action associée (Save ou Load)
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Color color;
        sf::Color hoverColor;
        bool isHovered = false;
    };

    class View {
    private:
        sf::Font font;
        sf::RectangleShape panelBackground;
        std::vector<Slider> sliders;
        std::vector<Button> buttons;

        // Largeur du menu de gauche
        float panelWidth = 300.0f;

    public:
        View();

        void initUI(Settings& settings);

        UiAction handleInput(const sf::Event& event, const sf::RenderWindow& window);

        void updateUI(const sf::RenderWindow& window);

        void draw(sf::RenderWindow& window, const Flock& flock);

        float getPanelWidth() const { return panelWidth; }
    };

}

#endif