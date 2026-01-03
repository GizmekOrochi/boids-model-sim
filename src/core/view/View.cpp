#include "../../include/view/View.hpp"
#include <cmath>
#include <iostream>

namespace bd {

View::View() {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "ERREUR: Impossible de charger une police" << std::endl;}


    panelBackground.setFillColor(sf::Color(50, 50, 50));
    panelBackground.setPosition(0, 0);
}

void View::initUI(Settings& s) {
    sliders.clear();
    buttons.clear();

    // --- 1. AJOUT DES BOUTONS ---
    // On place les boutons en haut
    Button btnSave;
    btnSave.label = "Sauvegarder";
    btnSave.action = UiAction::Save;
    btnSave.position = sf::Vector2f(20.0f, 20.0f);
    btnSave.size = sf::Vector2f(120.0f, 30.0f);
    btnSave.color = sf::Color(70, 70, 70);
    btnSave.hoverColor = sf::Color(100, 100, 100);
    buttons.push_back(btnSave);

    Button btnLoad;
    btnLoad.label = "Charger";
    btnLoad.action = UiAction::Load;
    btnLoad.position = sf::Vector2f(160.0f, 20.0f); // Décalé à droite
    btnLoad.size = sf::Vector2f(120.0f, 30.0f);
    btnLoad.color = sf::Color(70, 70, 70);
    btnLoad.hoverColor = sf::Color(100, 100, 100);
    buttons.push_back(btnLoad);

    // --- 2. AJOUT DES SLIDERS ---
    // On descend le startY pour laisser la place aux boutons
    float startY = 80.0f;
    float gap = 60.0f;

    auto add = [&](const std::string& name, float* val, float min, float max, int index) {
        Slider sl;
        sl.label = name;
        sl.valueRef = val;
        sl.minVal = min;
        sl.maxVal = max;
        sl.position = sf::Vector2f(20.0f, startY + index * gap);
        sl.width = 240.0f;
        sl.height = 10.0f;
        sl.isDragging = false;
        sliders.push_back(sl);
    };

    int i = 0;
    add("Cohesion",       &s.cohesionweight,     0.0f, 0.1f,   i++);
    add("Separation",     &s.separationweight,   0.0f, 5.0f,   i++);
    add("Alignement",     &s.alignmentweight,    0.0f, 0.5f,   i++);
    add("Rayon Perception", &s.perceptionRadius, 10.0f, 200.0f, i++);
    add("Dist. Separation", &s.separationDistance, 5.0f, 100.0f, i++);
    add("Vitesse Max",    &s.maxSpeed,           1.0f, 10.0f,  i++);
    add("Force Max",      &s.maxAcceleration,    0.01f, 1.0f,  i++);
}

UiAction View::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float mx = static_cast<float>(mousePos.x);
        float my = static_cast<float>(mousePos.y);

        // A. Vérifier les SLIDERS
        for (auto& s : sliders) {
            sf::FloatRect bounds(s.position.x, s.position.y - 15, s.width, 40);
            if (bounds.contains(mx, my)) {
                s.isDragging = true;
            }
        }

        // B. Vérifier les BOUTONS
        for (const auto& btn : buttons) {
            sf::FloatRect bounds(btn.position, btn.size);
            if (bounds.contains(mx, my)) {
                return btn.action; // On renvoie l'action (Save ou Load)
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        for (auto& s : sliders) s.isDragging = false;
    }

    return UiAction::None; // Aucune action spéciale
}

void View::updateUI(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float mx = static_cast<float>(mousePos.x);
    float my = static_cast<float>(mousePos.y);

    // 1. Mise à jour Sliders (Drag)
    for (auto& s : sliders) {
        if (s.isDragging) {
            float ratio = (mx - s.position.x) / s.width;
            if (ratio < 0.0f) ratio = 0.0f;
            if (ratio > 1.0f) ratio = 1.0f;
            *s.valueRef = s.minVal + ratio * (s.maxVal - s.minVal);
        }
    }

    // 2. Mise à jour Boutons (Hover effect)
    for (auto& btn : buttons) {
        sf::FloatRect bounds(btn.position, btn.size);
        btn.isHovered = bounds.contains(mx, my);
    }
}

void View::draw(sf::RenderWindow& window, const Flock& flock) {
    // Fond Panneau
    panelBackground.setSize(sf::Vector2f(panelWidth, static_cast<float>(window.getSize().y)));
    window.draw(panelBackground);

    // Dessin des BOUTONS
    for (const auto& btn : buttons) {
        sf::RectangleShape rect(btn.size);
        rect.setPosition(btn.position);
        // Change la couleur si la souris est dessus
        rect.setFillColor(btn.isHovered ? btn.hoverColor : btn.color);
        rect.setOutlineThickness(1);
        rect.setOutlineColor(sf::Color::White);
        window.draw(rect);

        sf::Text text;
        text.setFont(font);
        text.setString(btn.label);
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::White);

        // Centrer le texte dans le bouton
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width/2.0f, textBounds.top + textBounds.height/2.0f);
        text.setPosition(btn.position.x + btn.size.x/2.0f, btn.position.y + btn.size.y/2.0f);

        window.draw(text);
    }

    // Dessin des SLIDERS (Code existant inchangé)
    for (const auto& s : sliders) {
        sf::Text text;
        text.setFont(font);
        text.setString(s.label + ": " + std::to_string(*s.valueRef));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::White);
        text.setPosition(s.position.x, s.position.y - 20);
        window.draw(text);

        sf::RectangleShape track(sf::Vector2f(s.width, s.height));
        track.setPosition(s.position);
        track.setFillColor(sf::Color(150, 150, 150));
        window.draw(track);

        float ratio = (*s.valueRef - s.minVal) / (s.maxVal - s.minVal);
        sf::RectangleShape knob(sf::Vector2f(10, 20));
        knob.setOrigin(5, 5);
        knob.setPosition(s.position.x + ratio * s.width, s.position.y + 5);
        knob.setFillColor(sf::Color::White);
        window.draw(knob);
    }

    // Dessin des BOIDS (Code existant)
    const auto& boids = flock.getBoids();
    for (size_t i = 0; i < boids.getsize(); ++i) {
        const Boid& b = boids[i];
        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(0, -6));
        triangle.setPoint(1, sf::Vector2f(12, 0));
        triangle.setPoint(2, sf::Vector2f(0, 6));
        triangle.setFillColor(sf::Color::White);
        float angle = std::atan2(b.velocity.y, b.velocity.x) * 180.f / 3.14159f;
        triangle.setRotation(angle);
        triangle.setPosition(b.position.x + panelWidth, b.position.y);
        window.draw(triangle);
    }
}

}