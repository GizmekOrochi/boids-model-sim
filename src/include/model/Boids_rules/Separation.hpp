#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

    /**
     * @class Separation
     * @brief Règle de Séparation.
     * * Cette règle empêche les boids de se chevaucher ou d'être trop proches les uns des autres.
     * Elle génère une force répulsive opposée à la direction des voisins trop proches.
     */
    class Separation : public Rule {
    public:
        /**
         * @brief Applique la règle de séparation.
         * * @param b Le boid courant.
         * @param ctx Le contexte contenant les voisins.
         * @return Vec3<float> Vecteur de répulsion pour s'éloigner des voisins trop proches.
         */
        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const override;
    };

}


#endif // SEPARATION_HPP