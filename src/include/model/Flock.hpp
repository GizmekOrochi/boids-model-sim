#ifndef FLOCK_HPP
#define FLOCK_HPP

#pragma once
#include "utils/DynamicArray.hpp"
#include "Boids_rules/Rule.hpp"
#include "Boid.hpp"
#include "../config/Settings.hpp"

namespace bd {

/**
 * @brief Manages a collection of boids and their flocking behavior.
 *
 * The Flock class owns a set of boids and a set of behavioral rules.
 * It is responsible for neighbor detection, rule evaluation, and
 * computation of the next velocity state for each boid based on
 * the active rules and simulation settings.
 */
class Flock {
private:
    /** Container holding all boids in the flock. */
    DynamicArray<Boid> boids;

    /** Container holding pointers to behavioral rules. */
    DynamicArray<Rule*> rules;

    /** Configuration parameters controlling flock behavior. */
    Settings settings;

private:
    /**
     * @brief Finds neighboring boids for a given boid.
     *
     * Neighbor selection is based on the flock's perception
     * parameters defined in the settings.
     *
     * @param index Index of the boid whose neighbors are queried.
     * @return A DynamicArray containing neighboring boids.
     */
    DynamicArray<Boid> findNeighbors(size_t index) const;

    /**
     * @brief Computes the combined force from all rules.
     *
     * Each rule contributes a force based on the boid and its
     * neighbors; the sum of these forces is returned.
     *
     * @param b The boid for which forces are computed.
     * @param neighbors The neighboring boids.
     * @return The resulting force vector.
     */
    Vec2<float> computeRuleForces(const Boid& b, const DynamicArray<Boid>& neighbors) const;

    /**
     * @brief Enforces a minimum base speed for a boid.
     *
     * If the boid has no neighbors or insufficient velocity,
     * its speed is adjusted according to the settings.
     *
     * @param b The boid to update.
     * @param neighbors The neighboring boids.
     */
    void enforceBaseSpeed(Boid& b, const DynamicArray<Boid>& neighbors);

    /**
     * @brief Clamps the magnitude of an acceleration vector.
     *
     * @param force The input force vector.
     * @return A force vector limited to the maximum acceleration.
     */
    Vec2<float> clampAcceleration(const Vec2<float>& force) const;

    /**
     * @brief Clamps the magnitude of a velocity vector.
     *
     * @param v The input velocity vector.
     * @return A velocity vector limited to the maximum speed.
     */
    Vec2<float> clampSpeed(const Vec2<float>& v) const;

public:
    /**
     * @brief Constructs an empty flock.
     */
    Flock() = default;

    /**
     * @brief Provides mutable access to the flock settings.
     *
     * @return Reference to the settings object.
     */
    Settings& getSettings() { return settings; }

    /**
     * @brief Provides read-only access to the flock settings.
     *
     * @return Const reference to the settings object.
     */
    const Settings& getSettings() const { return settings; }

    /**
     * @brief Provides mutable access to the boid container.
     *
     * @return Reference to the DynamicArray of boids.
     */
    DynamicArray<Boid>& getBoids() { return boids; }

    /**
     * @brief Provides read-only access to the boid container.
     *
     * @return Const reference to the DynamicArray of boids.
     */
    const DynamicArray<Boid>& getBoids() const { return boids; }

    /**
     * @brief Adds a boid to the flock.
     *
     * @param b The boid to add.
     */
    void addBoid(const Boid& b) { boids.push_back(b); }

    /**
    * @brief Removes the last boid from the flock.
    *
    * Does nothing if the flock is empty.
    */
    void removeLastBoid() {
        if (boids.getsize() > 0)
            boids.pop_back();
    }

    /**
     * @brief Adds a behavioral rule to the flock.
     *
     * @param rule Pointer to the rule to add.
     */
    void addRule(Rule* rule) { rules.push_back(rule); }

    /**
     * @brief Retrieves a rule of a specific type.
     *
     * Performs a dynamic cast on all stored rules and returns
     * the first rule matching the requested type.
     *
     * @tparam T Type of the rule to retrieve.
     * @return Pointer to the rule if found, otherwise nullptr.
     */
    template <typename T>
    T* getRule() {
        for (size_t i = 0; i < rules.getsize(); ++i)
            if (auto* r = dynamic_cast<T*>(rules[i]))
                return r;
        return nullptr;
    }

    /**
     * @brief Removes all boids from the flock.
     *
     * This function is primarily used during save/load operations
     * to reset the flock state.
     */
    void clearBoids() {
        boids.clear();
    }

    /**
     * @brief Computes the next velocity for each boid.
     *
     * This function evaluates neighbors and rules for all boids
     * and returns a list of resulting velocity vectors.
     *
     * @return A DynamicArray containing the next velocities.
     */
    DynamicArray<Vec2<float>> computeNextVelocities();
};

}

#endif // FLOCK_HPP
