#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "utils/ui_types.hpp"
#include "View3D.hpp"
#include "ViewLayout.hpp"


namespace bd {

/**
 * @class View
 * @brief Classe principale de la couche Vue.
 * * Cette classe agit comme un conteneur central qui agrège :
 * 1. Le rendu de la scène 3D (via View3D).
 * 2. La structure de l'interface utilisateur 2D (via ViewLayout).
 * Elle fournit les accès nécessaires au Contrôleur pour dessiner et mettre à jour l'application.
 */
class View {
public:
    /**
     * @brief Constructeur de la Vue principale.
     * @param font Référence vers la police d'écriture utilisée pour toute l'interface.
     * @param w Largeur initiale de la fenêtre.
     * @param h Hauteur initiale de la fenêtre.
     */
    View(sf::Font& font, int w, int h);

    /**
     * @brief Accède à la caméra de la scène 3D.
     * * Permet de modifier la position ou l'angle de vue.
     * @return Référence vers l'objet Camera contenu dans View3D.
     */
    Camera& getCamera();

    /**
     * @brief Récupère le moteur de rendu 3D.
     * @return L'objet View3D responsable du dessin des boids et du monde.
     */
    View3D getView3D() { return view3D;}

    /**
     * @brief Accède à la liste des boutons de l'interface.
     * * Utile pour le contrôleur afin de gérer les clics.
     * @return Référence vers le vecteur de boutons géré par ViewLayout.
     */
    std::vector<Button>& getButtons() { return viewlayout.buttons; };

    /**
     * @brief Accède à la liste des sliders de l'interface.
     * * Utile pour le contrôleur afin de gérer les changements de valeurs.
     * @return Référence vers le vecteur de sliders géré par ViewLayout.
     */
    std::vector<Slider>& getSliders() { return viewlayout.sliders; };

    /**
     * @brief Dessine l'interface utilisateur (HUD) par-dessus la 3D.
     * * Affiche les boutons, les sliders et leurs textes associés.
     * @param win La fenêtre de rendu SFML.
     * @param buttons La liste des boutons à dessiner.
     * @param sliders La liste des sliders à dessiner.
     */
    void drawUI(sf::RenderWindow& win, const std::vector<Button>& buttons, const std::vector<Slider>& sliders);

    /**
     * @brief Méthode générique de dessin.
     * * Peut être utilisée pour orchestrer l'ordre de rendu global (Fond -> 3D -> UI).
     */
    void draw(sf::RenderWindow& win);

    /**
     * @brief Met à jour les dimensions du viewport .
     * * À appeler lors du redimensionnement de la fenêtre pour ajuster la projection 3D et l'UI.
     * @param w Nouvelle largeur.
     * @param h Nouvelle hauteur.
     */
    void setViewport(int w, int h);


private:
    sf::Font& font;         ///< Référence vers la ressource de police .
    View3D view3D;          ///< Sous-système de rendu 3D.
    ViewLayout viewlayout;  ///< Sous-système de gestion de la mise en page UI.
};

}

#endif