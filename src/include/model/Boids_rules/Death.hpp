#ifndef DEATH_HPP
#define DEATH_HPP

#include "Rule.hpp"

namespace bd {

    /**
     * @class Death
     * @brief Règle de gestion de la mortalité.
     * * Contrairement aux autres règles qui influencent le mouvement, cette règle
     * vérifie si le boid a été "attrapé" par un prédateur.
     * Si c'est le cas, elle marque le boid pour suppression (via la liste `eaten` du contexte).
     */
    class Death : public Rule {
    public:
        /**
         * @brief Vérifie les conditions de mort.
         * * Parcourt les prédateurs proches. Si l'un d'eux est à portée de contact,
         * l'ID du boid actuel est ajouté à la liste des boids mangés (`ctx.eaten`).
         * * @param b Le boid courant (proie potentielle).
         * @param ctx Le contexte contenant les prédateurs et la liste de sortie `eaten`.
         * @return Vec3<float> Renvoie généralement un vecteur nul (0,0,0) car la mort n'est pas une force de mouvement, mais un changement d'état.
         */
        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const override;
    };

} // namespace bd

#endif // DEATH_HPP