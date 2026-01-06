#ifndef FLOCK_HPP
#define FLOCK_HPP

#pragma once
#include "utils/DynamicArray.hpp"
#include "utils/Vec3.hpp"
#include "utils/Species.hpp"
#include "Boids_rules/Rule.hpp"
#include "Boid.hpp"
#include "../config/Settings.hpp"

namespace bd {

class Flock {
private:
    DynamicArray<Boid> boids;
    DynamicArray<Rule*> rules;

    DynamicArray<size_t> findNeighbors(size_t index) const;

    Vec3<float> computeRuleForces(const Boid& b, const DynamicArray<size_t>& neighbors) const;

    void enforceBaseSpeed(
        Boid& b,
        const DynamicArray<size_t>& neighbors
    );

    Vec3<float> clampAcceleration(const Vec3<float>& force) const;
    Vec3<float> clampSpeed(const Vec3<float>& v) const;

public:
    Flock() = default;

    DynamicArray<Boid>& getBoids() { return boids; }
    const DynamicArray<Boid>& getBoids() const { return boids; }

    void addBoid(const Boid& b) { boids.push_back(b); }

    void removeLastBoid() {
        if (boids.getsize() > 0)
            boids.pop_back();
    }

    void addRule(Rule* rule) { rules.push_back(rule); }

    template <typename T>
    T* getRule() {
        for (size_t i = 0; i < rules.getsize(); ++i) {
            if (auto* r = dynamic_cast<T*>(rules[i]))
                return r;
        }
        return nullptr;
    }

    void clearBoids() {
        boids.clear();
    }

    DynamicArray<Vec3<float>> computeNextVelocities();
};

}

#endif // FLOCK_HPP