#ifndef BOID_HPP
#define BOID_HPP

#pragma once
#include "utils/Vec3.hpp"
#include "utils/Species.hpp"
#include "../config/Settings.hpp"

namespace bd {

    /**
     * @brief Représente un agent unique boid dans la simulation.
     *
     * Un Boid encapsule l'état physique minimal requis par la simulation :
     * sa position dans l'espace et son vecteur vitesse.
     * Les règles comportementales opèrent sur ces valeurs pour produire
     * le mouvement de nuée.
     */
    class Boid {
    public:
        /** Position actuelle du boid dans l'espace monde. */
        Vec3<float> position;

        /** Vecteur vitesse actuel du boid. */
        Vec3<float> velocity;

        /** Espèce actuelle du boid (détermine son comportement et sa couleur). */
        Species::BoidSpecies specie;

        /** Identifiant unique du boid. */
        int ID;

        /**
         * @brief Construit un boid à l'origine (0,0,0) avec une vitesse nulle.
         * @param specie L'espèce du boid à créer.
         */
        Boid(Species::BoidSpecies specie) : position(0.0f,0.0f,0.0f), velocity(0.0f,0.0f,0.0f), specie(specie), ID(settings::currentIDAvalible) {
            settings::currentIDAvalible++;
        }

        /**
         * @brief Construit un boid à une position donnée avec une vitesse nulle.
         *
         * @param x Coordonnée X initiale.
         * @param y Coordonnée Y initiale.
         * @param z Coordonnée Z initiale.
         * @param specie L'espèce du boid.
         */
        Boid(float x, float y, float z, Species::BoidSpecies specie) : position(x,y,z), velocity(0.0f,0.0f,0.0f), specie(specie), ID(settings::currentIDAvalible) {
            settings::currentIDAvalible++;
        }

        /**
         * @brief Destructeur du boid.
         * Décrémente le compteur global d'IDs disponibles.
         */
        ~Boid() { settings::currentIDAvalible--; }
    };

}

#endif // BOID_HPP