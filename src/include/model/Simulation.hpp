#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#pragma once
#include "World.hpp"
#include "Flock.hpp"
#include "Obstacle.hpp"
#include "../model/Boids_rules/Cohesion.hpp"
#include "../model/Boids_rules/Separation.hpp"
#include "../model/Boids_rules/Alignment.hpp"
#include "../model/Boids_rules/Avoidance.hpp"
#include "../model/Boids_rules/Death.hpp"

namespace bd {

/**
 * @class Simulation
 * @brief Coordonne la simulation d'une nuée (Flock) au sein d'un monde (World).
 *
 * La classe Simulation possède à la fois le Monde et la Nuée et est
 * responsable de l'avancement de l'état de la simulation au fil du temps.
 * Elle sert de composant central du modèle, orchestrant les mises à jour
 * sans gérer les aspects de rendu graphique ou d'entrées utilisateur.
 */
class Simulation {
private:
    /** Le monde dans lequel la simulation se déroule (contraintes spatiales). */
    World world;

    /** La nuée (ensemble d'agents) simulée dans ce monde. */
    Flock flock;

    /** Le pas de temps utilisé pour avancer la simulation à chaque mise à jour. */
    float deltaTime;

    /** Tableau dynamique stockant les identifiants des boids mangés (morts). */
    DynamicArray<int>* eaten;

    /**
     * @brief Initialise la Nuée.
     * * Configure et ajoute les règles comportementales par défaut (Cohésion, Séparation, etc.).
     */
    void init();

public:
    /**
     * @brief Construit une simulation avec un pas de temps donné.
     *
     * @param dt Le delta temps (pas de temps) utilisé pour chaque mise à jour de la simulation.
     */
    Simulation(float dt);

    /**
     * @brief Destructeur de la simulation.
     * * Libère la mémoire allouée dynamiquement (liste des boids mangés).
     */
    ~Simulation() { delete eaten; };

    /**
     * @brief Fournit un accès modifiable au monde.
     *
     * @return Référence vers l'objet World.
     */
    World& getWorld() { return world; }

    /**
     * @brief Fournit un accès modifiable à la nuée.
     *
     * @return Référence vers l'objet Flock.
     */
    Flock& getFlock() { return flock; }

    /**
     * @brief Fournit un accès en lecture seule au monde.
     *
     * @return Référence constante vers l'objet World.
     */
    const World& getWorld() const { return world; }

    /**
     * @brief Fournit un accès en lecture seule à la nuée.
     *
     * @return Référence constante vers l'objet Flock.
     */
    const Flock& getFlock() const { return flock; }

    /**
     * @brief Avance la simulation d'un pas de temps.
     *
     * Cette fonction met à jour l'état de la nuée en fonction de ses règles
     * et applique les contraintes du monde en utilisant le delta temps configuré.
     */
    void update();


    // Toutes ces méthodes sont des accesseurs (proxies) vers les méthodes de Flock pour le contrôleur

    /**
     * @brief Ajoute un boid à la simulation.
     * @param b Le boid à ajouter.
     */
    void addBoid(const Boid& b) { flock.addBoid(b); }

    /**
     * @brief Retire le dernier boid ajouté.
     */
    void removeLastBoid() { flock.removeLastBoid(); }

    /**
     * @brief Ajoute un obstacle à la simulation.
     * @param o L'obstacle à ajouter.
     */
    void addObstacle(const Obstacle& o) { flock.addObstacle(o); }

    /**
     * @brief Retire le dernier obstacle ajouté.
     */
    void removeLastObstacle() { flock.removeLastObstacle(); }

    /**
     * @brief Supprime tous les boids de la simulation.
     */
    void clearBoids() { flock.clearBoids(); }

    /**
     * @brief Accède au tableau dynamique des boids.
     * @return Référence vers le tableau des boids.
     */
    DynamicArray<Boid>& getBoids() { return flock.getBoids(); }

    /**
     * @brief Accède au tableau dynamique des obstacles.
     * @return Référence vers le tableau des obstacles.
     */
    DynamicArray<Obstacle>& getObstacles() { return flock.getObstacles(); }

    /**
     * @brief Récupère un boid spécifique par son index.
     * @param index L'index du boid dans le tableau.
     * @return Référence vers le boid.
     */
    Boid& getBoid(size_t index) { return flock.getBoids()[index]; }

    /**
     * @brief Récupère le nombre actuel de boids dans la simulation.
     * @return Le nombre de boids (taille du tableau).
     */
    size_t getBoidSize() { return flock.getBoids().getsize(); }

    /**
     * @brief Supprime les boids mangés de la liste principale.
     * * Parcourt la liste des IDs mangés et retire les boids correspondants de la simulation.
     * @param boids La liste des boids actifs.
     * @param eaten La liste des IDs des boids à supprimer.
     */
    void removeEatenBoids(DynamicArray<Boid>& boids, const DynamicArray<int>& eaten);
};

}

#endif // SIMULATION_HPP