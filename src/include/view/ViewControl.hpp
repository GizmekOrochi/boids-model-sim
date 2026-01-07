#ifndef VIEW_CONTROL_HPP
#define VIEW_CONTROL_HPP

#include <SFML/Graphics.hpp>
#include "ui_types.hpp"
#include "utils/Camera.hpp"

namespace bd {

/**
 * @class ViewControl
 * @brief Contrôleur principal des entrées utilisateur (Input).
 * * Cette classe fait le lien entre les événements bruts de la fenêtre (clavier, souris)
 * et la logique de l'application. Elle gère à la fois l'interaction avec les éléments 2D (UI)
 * et le pilotage de la caméra 3D.
 */
class ViewControl {
public:
    /**
     * @brief Traite les événements discrets (clics, touches pressées).
     * * Cette méthode doit être appelée dans la boucle d'événements de SFML (pollEvent).
     * Elle vérifie si un événement (comme un clic souris) a interagi avec un bouton ou un slider.
     * * @param event L'événement SFML brut à traiter.
     * @param window La fenêtre de rendu (pour connaître les coordonnées de la souris).
     * @param buttons La liste des boutons à vérifier.
     * @param sliders La liste des sliders à vérifier.
     * @return UiAction L'action déclenchée par l'interface (ex: START_SIMULATION, NONE).
     */
    UiAction handleEvent(const sf::Event& event, const sf::RenderWindow& window, std::vector<Button>& buttons, std::vector<Slider>& sliders);

    /**
     * @brief Met à jour l'état visuel continu de l'interface.
     * * Cette méthode gère les interactions qui ne dépendent pas d'un clic unique,
     * comme le survol de la souris (hover effect) ou le glissement maintenu d'un slider.
     * * @param window La fenêtre de rendu.
     * @param buttons La liste des boutons (pour mettre à jour leur couleur au survol).
     * @param sliders La liste des sliders (pour mettre à jour la position du curseur).
     */
    void update(const sf::RenderWindow& window, std::vector<Button>& buttons, std::vector<Slider>& sliders);

    /**
     * @brief Contrôle les mouvements de la caméra 3D.
     * * Gère les déplacements (Z,Q,S,D ou W,A,S,D) et la rotation de la vue
     * en fonction des entrées clavier et souris en temps réel.
     * * @param cam La référence vers la caméra à déplacer.
     * @param dt Le temps écoulé depuis la dernière frame (delta time) pour lisser le mouvement.
     */
    void updateCamera(Camera& cam, float dt);
};

}

#endif