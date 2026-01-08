#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#pragma once
#include <string>
#include "utils/Vec3.hpp"
#include "utils/MathsVector.hpp"


namespace bd {

/**
 * @class Obstacle
 * @brief Représente un obstacle statique dans la simulation.
 *
 * Un obstacle est une entité physique (généralement cubique) qui ne bouge pas
 * et n'obéit à aucune règle de comportement, mais que les boids doivent éviter.
 */
class Obstacle {
public:
    /** Position actuelle de l'obstacle dans l'espace monde. */
    Vec3<float> position;

    int sizeX;
    int sizeY;
    int sizeZ;

    /**
     * @brief Construit un obstacle par défaut à l'origine.
     */
    Obstacle() : position(0.0f,0.0f,0.0f), sizeX(10.0f), sizeY(10.0f), sizeZ(10.0f) {}

    /**
     * @brief Construit un obstacle avec une position et une taille données.
     *
     * @param x Coordonnée X.
     * @param y Coordonnée Y.
     * @param z Coordonnée Z.
     * @param sizeX Largeur.
     * @param sizeY Hauteur.
     * @param sizeZ Profondeur.
     */
    Obstacle(float x, float y, float z, int sizeX, int sizeY, int sizeZ) : position(x,y,z), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {}
};

} //namespace


#endif // OBSTACLE_HPP