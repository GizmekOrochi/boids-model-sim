#ifndef FLOCK_HPP
#define FLOCK_HPP

#pragma once
#include "DynamicArray.hpp"
#include "Rule.hpp"
#include "Boid.hpp"

namespace bd {

class Flock {
private:
    DynamicArray<Boid> boids;
    DynamicArray<Rule*> rules;

public:
    Flock() = default;

    void addBoid(const Boid& b) { boids.push_back(b); }
    void addRule(Rule* rule) { rules.push_back(rule); }

    DynamicArray<Boid>& getBoids() { return boids; }

    void update(float dt);
};

} // namespace bd


#endif // FLOCK_HPP
