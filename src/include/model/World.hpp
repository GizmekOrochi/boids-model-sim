#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once
#include "Boid.hpp"
#include "../config/Settings.hpp"

namespace bd {

/**
 * @class World
 * @brief Définit les limites spatiales de la simulation.
 * * Le monde est représenté par un volume rectangulaire  défini par sa largeur,
 * sa hauteur et sa profondeur. Cette classe est responsable de la gestion des limites,
 * en s'assurant que les boids restent à l'intérieur ou rebondissent contre les parois.
 */
class World {
public:
    /**
     * @brief Constructeur par défaut.
     * * Initialise les dimensions du monde en utilisant les valeurs définies
     * dans les paramètres globaux.
     */
    World() = default;

    /**
     * @brief Constructeur avec dimensions personnalisées.
     * @param w Largeur du monde (axe X).
     * @param h Hauteur du monde (axe Y).
     * @param d Profondeur du monde (axe Z).
     */
    World(float w, float h, float d) : width(w), height(h), depth(d) {}

    /**
     * @brief Récupère la largeur du monde.
     * @return La largeur (axe X).
     */
    float getWidth() const { return width; }

    /**
     * @brief Récupère la hauteur du monde.
     * @return La hauteur (axe Y).
     */
    float getHeight() const { return height; }

    /**
     * @brief Récupère la profondeur du monde.
     * @return La profondeur (axe Z).
     */
    float getDepth() const { return depth; }

    /**
     * @brief Applique les contraintes de bordure au boid.
     * * Vérifie si le boid sort des limites du monde. Si c'est le cas, cette méthode
     * corrige sa position et inverse sa vitesse pour le maintenir à l'intérieur.
     * @param b Le boid à vérifier et corriger.
     */
    void handleBoundaries(Boid& b) const;

private:
    /** Largeur du monde (limite sur l'axe X). */
    float width = settings::worldWidth;

    /** Hauteur du monde (limite sur l'axe Y). */
    float height = settings::worldHeight;

    /** Profondeur du monde (limite sur l'axe Z). */
    float depth = settings::worldDeepth;
};

}

#endif // WORLD_HPP