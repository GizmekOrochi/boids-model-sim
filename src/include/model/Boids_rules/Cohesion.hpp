#ifndef COHESION_HPP
#define COHESION_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

    /**
     * @class Cohesion
     * @brief Règle de Cohésion.
     * * Cette règle pousse le boid à se diriger vers le centre de masse
     * de ses voisins locaux. Elle maintient le groupe uni.
     */
    class Cohesion : public Rule {
    public:
        /** Facteur de pondération de la règle. */
        float weight = settings::cohesionWeight;

        /**
         * @brief Applique la règle de cohésion.
         * * Calcule la position moyenne des voisins et génère une force attractive vers ce point.
         * * @param b Le boid courant.
         * @param ctx Le contexte contenant les voisins.
         * @return Vec3<float> Vecteur de force vers le centre du groupe local.
         */
        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const override;
    };

}

#endif // COHESION_HPP