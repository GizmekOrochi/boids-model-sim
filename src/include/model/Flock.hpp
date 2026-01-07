#ifndef FLOCK_HPP
#define FLOCK_HPP

#pragma once

#include "utils/DynamicArray.hpp"
#include "utils/Vec3.hpp"
#include "utils/Species.hpp"
#include "Boids_rules/Rule.hpp"
#include "Boid.hpp"
#include "Obstacle.hpp"
#include "../config/Settings.hpp"

namespace bd {

/**
 * @class Flock
 * @brief Gère un groupe Boids et leur environnement immédiat.
 * * La classe Flock est le conteneur principal des entités dynamiques de la simulation.
 * Elle stocke les boids, les obstacles et les règles comportementales à appliquer.
 * Elle est responsable de l'étape la plus coûteuse : le calcul des voisinages et
 * l'application des forces pour chaque agent.
 */
class Flock {
private:
    /** Liste dynamique de tous les boids présents dans la simulation. */
    DynamicArray<Boid> boids;

    /** Liste dynamique des obstacles passifs. */
    DynamicArray<Obstacle> obstacles;

    /** Liste des règles de comportement actives (ex: Cohésion, Séparation, Alignement). */
    DynamicArray<Rule*> rules;

    /**
     * @brief Identifie les voisins et les prédateurs pour un boid donné.
     * * Parcourt tous les autres boids pour trouver ceux qui sont dans le rayon de perception
     * et dans le champ de vision (angle). Trie les résultats en "voisins" (amis) ou "prédateurs" (menaces).
     * * @param index L'index du boid courant dans le tableau.
     * @param neighbors [Sortie] Liste des indices des voisins amicaux.
     * @param predators [Sortie] Liste des indices des prédateurs détectés.
     */
    void findNeighbors(size_t index, DynamicArray<size_t>& neighbors, DynamicArray<size_t>& predators) const;

    /**
     * @brief Calcule la force résultante de toutes les règles pour un boid.
     * * @param b Le boid courant.
     * @param neighbors Liste des indices des voisins.
     * @param predators Liste des indices des prédateurs.
     * @param eaten Pointeur vers la liste des boids mangés (pour la règle de mort).
     * @return Vec3<float> Le vecteur force accumulé à appliquer.
     */
    Vec3<float> computeRuleForces(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<size_t>& predators, DynamicArray<int>* eaten) const;

    /**
     * @brief Maintient une vitesse de base pour les boids isolés ou lents.
     * * Si un boid n'a pas de voisins ou est presque à l'arrêt, cette méthode lui
     * redonne une impulsion pour éviter que la simulation ne stagne.
     */
    void enforceBaseSpeed(Boid& b, const DynamicArray<size_t>& neighbors);

    /**
     * @brief Limite l'amplitude de la force (accélération) appliquée.
     * * Empêche des changements de direction physiquement impossibles ou trop brusques.
     * * @param force La force calculée.
     * @param hungeraccleration Facteur multiplicateur basé sur le niveau trophique (les prédateurs accélèrent plus vite).
     * @return Vec3<float> La force tronquée à la valeur maximale définie.
     */
    Vec3<float> clampAcceleration(const Vec3<float>& force, float hungeraccleration) const;

    /**
     * @brief Limite la vitesse finale du boid.
     * * @param force La nouvelle vélocité potentielle (vitesse actuelle + force).
     * @return Vec3<float> La vélocité tronquée à la vitesse maximale (maxSpeed).
     */
    Vec3<float> clampSpeed(const Vec3<float>& force) const;

public:
    /**
     * @brief Constructeur par défaut.
     */
    Flock() = default;

    /**
     * @brief Accède à la liste des boids (modifiable).
     * @return Référence vers le tableau dynamique des boids.
     */
    DynamicArray<Boid>& getBoids() { return boids; }

    /**
     * @brief Accède à la liste des boids (lecture seule).
     * @return Référence constante vers le tableau dynamique des boids.
     */
    const DynamicArray<Boid>& getBoids() const { return boids; }

    /**
     * @brief Accède à la liste des obstacles (modifiable).
     * @return Référence vers le tableau dynamique des obstacles.
     */
    DynamicArray<Obstacle>& getObstacles() { return obstacles; }

    /**
     * @brief Accède à la liste des obstacles (lecture seule).
     * @return Référence constante vers le tableau dynamique des obstacles.
     */
    const DynamicArray<Obstacle>& getObstacles() const { return obstacles; }

    /**
     * @brief Ajoute un nouveau boid à la nuée.
     * @param b Le boid à ajouter.
     */
    void addBoid(const Boid& b) { boids.push_back(b); }

    /**
     * @brief Ajoute un nouvel obstacle à la simulation.
     * @param o L'obstacle à ajouter.
     */
    void addObstacle(const Obstacle& o) { obstacles.push_back(o); }

    /**
     * @brief Ajoute une règle comportementale à la liste active.
     * @param rule Pointeur vers la règle (doit être allouée dynamiquement ou gérée ailleurs).
     */
    void addRule(Rule* rule) { rules.push_back(rule); }

    /**
     * @brief Retire le dernier boid ajouté (LIFO).
     * * Utile pour l'interface utilisateur ("Retirer Boid").
     */
    void removeLastBoid() {
        if (boids.getsize() > 0)
            boids.pop_back();
    }

    /**
     * @brief Retire le dernier obstacle ajouté.
     */
    void removeLastObstacle() {
        if (obstacles.getsize() > 0)
            obstacles.pop_back();
    }

    /**
     * @brief Récupère une règle spécifique par son type.
     * * @tparam T Le type de la règle recherchée (ex: Separation).
     * @return T* Pointeur vers la règle trouvée, ou nullptr si elle n'existe pas.
     */
    template <typename T>
    T* getRule() {
        for (size_t i = 0; i < rules.getsize(); ++i) {
            if (auto* r = dynamic_cast<T*>(rules[i]))
                return r;
        }
        return nullptr;
    }

    /**
     * @brief Supprime tous les boids de la simulation.
     */
    void clearBoids() { boids.clear(); }

    /**
     * @brief Supprime tous les obstacles de la simulation.
     */
    void clearObstacles() { obstacles.clear(); }

    /**
     * @brief Calcule les prochaines vitesses pour tous les boids.
     * * C'est la méthode principale de mise à jour physique. Elle itère sur tous les boids,
     * calcule les voisins, applique les règles et renvoie les nouvelles vélocités.
     * * @param eaten Pointeur optionnel pour collecter les IDs des boids mangés durant ce tour.
     * @return DynamicArray<Vec3<float>> Liste des nouvelles vitesses calculées (correspondant aux indices des boids).
     */
    DynamicArray<Vec3<float>> computeNextVelocities(DynamicArray<int>* eaten);
};

}

#endif // FLOCK_HPP