#ifndef VIEW_LAYOUT_HPP
#define VIEW_LAYOUT_HPP

#include <vector>
#include "utils/ui_types.hpp"
#include "../config/Settings.hpp"

namespace bd {

    /**
     * @class ViewLayout
     * @brief Gère la structure et la disposition des éléments de l'interface utilisateur (UI).
     * * Cette classe agit comme un conteneur pour tous les widgets interactifs (boutons, sliders).
     * Elle est responsable de l'initialisation et du placement de ces éléments à l'écran.
     */
    class ViewLayout {
    public:
        /**
         * @brief Collection des boutons de l'interface.
         * * Contient tous les objets Button qui seront rendus et mis à jour par la vue.
         */
        std::vector<Button> buttons;

        /**
         * @brief Collection des sliders (curseurs) de l'interface.
         * * Contient tous les objets Slider permettant de modifier les valeurs numériques
         * (comme les paramètres de la simulation).
         */
        std::vector<Slider> sliders;

        /**
         * @brief Construit et initialise la disposition de l'interface.
         * * Cette méthode remplit les vecteurs `buttons` et `sliders` avec les éléments appropriés,
         * définit leurs positions, leurs tailles et leurs labels en fonction de la configuration actuelle.
         * Elle doit être appelée lors de l'initialisation de l'application.
         */
        void build();
    };

}

#endif