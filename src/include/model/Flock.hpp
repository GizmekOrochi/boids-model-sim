#ifndef FLOCK_HPP
#define FLOCK_HPP

#pragma once
#include "DynamicArray.hpp"
#include "Rule.hpp"
#include "Boid.hpp"
#include "../config/Settings.hpp"

namespace bd {

class Flock {
private:
    DynamicArray<Boid> boids;
    DynamicArray<Rule*> rules;
    Settings settings;

private:
    // --- Helper functions ---

    DynamicArray<Boid> findNeighbors(size_t index) const;

    Vec2<float> computeRuleForces(const Boid& b, const DynamicArray<Boid>& neighbors) const;

    void enforceBaseSpeed(Boid& b, const DynamicArray<Boid>& neighbors);

    Vec2<float> clampAcceleration(const Vec2<float>& force) const;

    Vec2<float> clampSpeed(const Vec2<float>& v) const;

    void moveBoid(Boid& b);

    void handleBoundaries(Boid& b);

public:
    Flock() = default;

    // Access settings
    Settings& getSettings() { return settings; }
    const Settings& getSettings() const { return settings; }

    // Access boids
    DynamicArray<Boid>& getBoids() { return boids; }
    const DynamicArray<Boid>& getBoids() const { return boids; }

    // Add boids and rules
    void addBoid(const Boid& b) { boids.push_back(b); }
    void addRule(Rule* rule) { rules.push_back(rule); }

    // Generic rule getter
    template <typename T>
    T* getRule() {
        for (size_t i = 0; i < rules.getsize(); i++)
            if (auto* r = dynamic_cast<T*>(rules[i]))
                return r;
        return nullptr;
    }

    // Main update
    void update();
};

}

#endif // FLOCK_HPP
