#ifndef RULE_HPP
#define RULE_HPP

#include "RuleContext.hpp"

namespace bd {

/**
 * @class Rule
 * @brief Interface abstraite pour tous les comportements de nuée.
 * * Chaque règle doit hériter de cette classe et implémenter la méthode `apply`.
 */
class Rule {
public:
    virtual ~Rule() = default;

    /**
     * @brief Calcule la force à appliquer au boid selon cette règle spécifique.
     * * Cette méthode purement virtuelle doit être définie par les sous-classes.
     * * @param b Le boid sur lequel la règle est appliquée.
     * @param ctx Le contexte environnemental (voisins, obstacles, prédateurs).
     * @return Vec3<float> Un vecteur force représentant la direction et l'intensité du mouvement désiré.
     */
    virtual Vec3<float> apply(const Boid& b, const RuleContext& ctx) const = 0;

};

}


#endif // RULE_HPP