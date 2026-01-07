#ifndef UI_TYPES_HPP
#define UI_TYPES_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace bd {

/**
 * @enum UiAction
 * @brief Énumération des commandes déclenchables par l'interface.
 * * Ces valeurs servent de signaux envoyés par la Vue au Contrôleur
 * lorsqu'un utilisateur interagit avec un bouton.
 */
enum class UiAction {
    None,           ///< Aucune action.
    AddBoid,        ///< Ajouter un nouvel agent (boid) dans la simulation.
    RmBoid,         ///< Supprimer le dernier agent ajouté.
    Save,           ///< Sauvegarder la configuration actuelle.
    Load,           ///< Charger une configuration.
    AddObstacle,    ///< Ajouter un obstacle au centre.
    RmObstacle,     ///< Retirer un obstacle.
    AddPredator     ///< Ajouter un prédateur (chasseur) dans la scène.
};

/**
 * @struct Slider
 * @brief Représente un widget de type "Curseur" (Slider) horizontal.
 * * Permet de modifier une valeur numérique flottante en faisant glisser la souris.
 * Le slider modifie directement la variable pointée par `valueRef`.
 */
struct Slider {
    std::string label;      ///< Texte affiché à côté du slider (ex: "Vitesse Max").

    /**
     * @brief Pointeur vers la variable à modifier.
     * * Ce pointeur lie le widget directement à une variable de configuration (ex: `settings::maxSpeed`).
     * Si la variable change ailleurs, le slider se met à jour visuellement, et inversement.
     */
    float* valueRef;

    float minVal;           ///< Valeur minimale de la plage.
    float maxVal;           ///< Valeur maximale de la plage.
    sf::Vector2f position;  ///< Position (x, y) du coin haut-gauche du slider à l'écran.
    float width;            ///< Largeur totale du slider en pixels.

    /**
     * @brief État d'interaction.
     * * True si l'utilisateur est en train de maintenir le clic et de glisser le curseur.
     */
    bool dragging = false;
};

/**
 * @struct Button
 * @brief Représente un widget de type "Bouton" cliquable.
 * * Un bouton possède une zone rectangulaire et déclenche une `UiAction` lorsqu'il est cliqué.
 */
struct Button {
    std::string label;      ///< Texte affiché sur le bouton.
    UiAction action;        ///< L'action qui sera renvoyée au contrôleur lors du clic.
    sf::Vector2f pos;       ///< Position (x, y) du coin haut-gauche du bouton.
    sf::Vector2f size;      ///< Dimensions (largeur, hauteur) du bouton.

    /**
     * @brief État visuel "Survolé".
     * * True si la souris est au-dessus du bouton (permet de changer la couleur pour le feedback visuel).
     */
    bool hovered = false;
};

}

#endif