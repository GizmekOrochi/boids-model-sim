#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

    /**
     * @class Alignment
     * @brief Règle d'Alignement.
     * * Cette règle incite le boid à aligner sa direction et sa vitesse sur celle
     * de la moyenne de ses voisins. Cela permet au groupe de se déplacer de manière coordonnée.
     */
    class Alignment : public Rule {
    public:
        /**
         * @brief Applique la règle d'alignement.
         * * Calcule la vitesse moyenne des voisins et génère une force pour s'y conformer.
         * * @param b Le boid courant.
         * @param ctx Le contexte contenant les voisins.
         * @return Vec3<float> Vecteur de force d'alignement.
         */
        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const override;
    };

}


#endif // ALIGNMENT_HPP