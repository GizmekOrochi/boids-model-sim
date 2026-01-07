#ifndef AVOIDANCE_HPP
#define AVOIDANCE_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

    /**
     * @class Avoidance
     * @brief Règle composite d'évitement (Murs, Obstacles, Prédateurs).
     * * Cette règle prioritaire assure la survie du boid en lui faisant éviter
     * les dangers immédiats de l'environnement.
     */
    class Avoidance : public Rule {
    public:
        /**
         * @brief Applique les règles d'évitement combinées.
         * * Agrège les forces d'évitement des limites du monde, des obstacles statiques
         * et des prédateurs actifs.
         * * @param b Le boid courant.
         * @param ctx Le contexte de simulation.
         * @return Vec3<float> La somme des forces d'évitement.
         */
        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const;

    private:
        /**
         * @brief Calcule la force pour rester dans les limites du monde.
         * * Si le boid s'approche trop d'un bord, une force opposée très forte est générée.
         */
        Vec3<float> avoidWorldBounds(const Boid& b) const;

        /**
         * @brief Calcule la force pour éviter les obstacles cubiques statiques.
         * * Utilise une détection de proximité pour contourner les obstacles.
         */
        Vec3<float> avoidObstacles(const Boid& b, const RuleContext& ctx) const;

        /**
         * @brief Calcule la force de fuite face aux prédateurs.
         * * Si un prédateur (défini dans `Species`) est proche, génère une force de fuite
         * dans la direction opposée.
         */
        Vec3<float> avoidPredators(const Boid& b, const RuleContext& ctx) const;
    };

}


#endif // AVOIDANCE_HPP