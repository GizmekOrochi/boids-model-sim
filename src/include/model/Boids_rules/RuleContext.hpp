#ifndef RULECONTEXT_HPP
#define RULECONTEXT_HPP

#include "Rule.hpp"
#include "../utils/Vec3.hpp"
#include "../utils/DynamicArray.hpp"
#include "../Obstacle.hpp"
#include "../Boid.hpp"
#include "../utils/Vec3.hpp"
#include "../../config/Settings.hpp"

namespace bd {

    /**
     * @struct RuleContext
     * @brief Contexte d'exécution pour le calcul des règles.
     * * Cette structure regroupe toutes les références nécessaires (voisins, prédateurs, obstacles)
     * pour qu'une règle puisse calculer sa force sans avoir une signature de méthode trop complexe.
     * Elle est recalculée pour chaque boid à chaque frame.
     */
    struct RuleContext {
        /** Référence vers la liste complète des boids (pour accéder aux données des voisins). */
        const DynamicArray<Boid>& boids;

        /** Indices des voisins proches du boid actuel dans le tableau `boids`. */
        const DynamicArray<size_t>& neighbors;

        /** Indices des prédateurs proches (si le boid est une proie). */
        const DynamicArray<size_t>& predator;

        /** Liste de tous les obstacles présents dans le monde. */
        const DynamicArray<Obstacle>& obstacles;

        /** Pointeur vers la liste des ID des boids mangés (utilisé par la règle Death). */
        DynamicArray<int>* eaten;
    };

} // namespace

#endif