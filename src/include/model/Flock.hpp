#ifndef FLOCK_HPP
#define FLOCK_HPP

#pragma once
#include "utils/DynamicArray.hpp"
#include "Boids_rules/Rule.hpp"
#include "Boid.hpp"
#include "../config/Settings.hpp"

namespace bd {

class Flock {
private:
    DynamicArray<Boid> boids;
    DynamicArray<Rule*> rules;
    Settings settings;

private:
    DynamicArray<Boid> findNeighbors(size_t index) const;
    Vec2<float> computeRuleForces(const Boid& b, const DynamicArray<Boid>& neighbors) const;

    void enforceBaseSpeed(Boid& b, const DynamicArray<Boid>& neighbors);

    Vec2<float> clampAcceleration(const Vec2<float>& force) const;
    Vec2<float> clampSpeed(const Vec2<float>& v) const;

public:
    Flock() = default;

    Settings& getSettings() { return settings; }
    const Settings& getSettings() const { return settings; }

    DynamicArray<Boid>& getBoids() { return boids; }
    const DynamicArray<Boid>& getBoids() const { return boids; }

    void addBoid(const Boid& b) { boids.push_back(b); }
    void addRule(Rule* rule) { rules.push_back(rule); }

    template <typename T>
    T* getRule() {
        for (size_t i = 0; i < rules.getsize(); ++i)
            if (auto* r = dynamic_cast<T*>(rules[i]))
                return r;
        return nullptr;
    }

    // Used to the save/reload process
    void clearBoids() {
        boids.clear();
    }

    DynamicArray<Vec2<float>> computeNextVelocities();
};

}

#endif // FLOCK_HPP
