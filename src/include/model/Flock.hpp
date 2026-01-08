#ifndef FLOCK_HPP
#define FLOCK_HPP

#pragma once

#include "utils/DynamicArray.hpp"
#include "utils/MathsVector.hpp"
#include "utils/Species.hpp"
#include "Boids_rules/Rule.hpp"
#include "Boid.hpp"
#include "Obstacle.hpp"
#include "../config/Settings.hpp"

namespace bd {


class Flock {
private:
    DynamicArray<Boid> boids;
    DynamicArray<Obstacle> obstacles;
    DynamicArray<Rule*> rules;

    MathsVector<float, 3> computeRuleForces(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<size_t>& predators, DynamicArray<int>* eaten) const;

    MathsVector<float, 3> clampAcceleration(const MathsVector<float, 3>& force, float hungeraccleration) const;
    MathsVector<float, 3> clampSpeed(const MathsVector<float, 3>& force) const;

    void enforceBaseSpeed(Boid& b, const DynamicArray<size_t>& neighbors);

    void findNeighbors(size_t index, DynamicArray<size_t>& neighbors, DynamicArray<size_t>& predators) const;

public:

    Flock() = default;

    DynamicArray<Boid>& getBoids() { return boids; }
    const DynamicArray<Boid>& getBoids() const { return boids; }

    DynamicArray<Obstacle>& getObstacles() { return obstacles; }
    const DynamicArray<Obstacle>& getObstacles() const { return obstacles; }

    void addBoid(const Boid& b) { boids.push_back(b); }
    void addObstacle(const Obstacle& o) { obstacles.push_back(o); }
    void addRule(Rule* rule) { rules.push_back(rule); }

    void removeLastBoid() {
        if (boids.getsize() > 0)
            boids.pop_back();
    }
    
    void removeLastObstacle() {
        if (obstacles.getsize() > 0)
            obstacles.pop_back();
    }

    template <typename T>
    T* getRule() {
        for (size_t i = 0; i < rules.getsize(); ++i) {
            if (auto* r = dynamic_cast<T*>(rules[i]))
                return r;
        }
        return nullptr;
    }

    void clearBoids() { boids.clear(); }
    void clearObstacles() { obstacles.clear(); }

    DynamicArray<MathsVector<float, 3>> computeNextVelocities(DynamicArray<int>* eaten);
};

}

#endif // FLOCK_HPP