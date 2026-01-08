#include "../../include/model/Flock.hpp"
#include <cmath>
#include <cstdlib>

namespace bd {

MathsVector<float, 3> Flock::computeRuleForces(const Boid& b, const DynamicArray<size_t>& neighbors,const DynamicArray<size_t>& predators, DynamicArray<int>* eaten) const {
    MathsVector<float, 3> total{};

    RuleContext ctx {
        .boids = boids,
        .neighbors = neighbors,
        .predator = predators,
        .obstacles = obstacles,
        .eaten = eaten
    };

    for (size_t i = 0; i < rules.getsize(); ++i) {
        if (rules[i])
            total += rules[i]->apply(b, ctx);
    }

    return total;
}

void Flock::enforceBaseSpeed(Boid& b, const DynamicArray<size_t>& neighbors) {
    if (neighbors.getsize() > 0)
        return;

    float len = b.velocity.length();

    if (len < 0.0001f) {
        float theta = float(rand()) / RAND_MAX * 2.f * 3.1415926f;
        float phi = float(rand()) / RAND_MAX * 3.1415926f;

        b.velocity = MathsVector<float, 3>{{std::sin(phi) * std::cos(theta), std::sin(phi) * std::sin(theta),std::cos(phi) * settings::baseSpeed}};
    }
    else if (len < settings::baseSpeed) {
        b.velocity = b.velocity.normalized() * settings::baseSpeed;
    }
}

MathsVector<float, 3> Flock::clampAcceleration(const MathsVector<float, 3>& force, float hungeraccleration) const {
    float len{force.length()};
    if (len > settings::maxAcceleration && len > 0.0f)
        return force.normalized() * settings::maxAcceleration;

    return force * hungeraccleration;
}


MathsVector<float, 3> Flock::clampSpeed(const MathsVector<float, 3>& force) const{
    float len{force.length()};
    if (len > settings::maxSpeed && len > 0.f)
        return force.normalized() * settings::maxSpeed;

    return force;
}

DynamicArray<MathsVector<float, 3>> Flock::computeNextVelocities(DynamicArray<int>* eaten) {
    DynamicArray<MathsVector<float, 3>> nextVelocities;
    DynamicArray<size_t> neighbors;
    DynamicArray<size_t> predators;

    for (size_t i = 0; i < boids.getsize(); ++i) {
        Boid& b = boids[i];

        findNeighbors(i, neighbors, predators);

        MathsVector<float, 3> force{computeRuleForces(b, neighbors, predators, eaten)};
        enforceBaseSpeed(b, neighbors);

        // Predator prey hunger boost
        float hungeraccleration = static_cast<float>(speciesTier(b.specie));

        force = clampAcceleration(force, hungeraccleration);
        MathsVector<float, 3> velocity{clampSpeed(b.velocity + force)};

        nextVelocities.push_back(velocity);
    }

    return nextVelocities;
}

void Flock::findNeighbors(size_t index, DynamicArray<size_t>& neighbors, DynamicArray<size_t>& predators) const{
    neighbors.clear();
    predators.clear();

    const Boid& b{boids[index]};
    const float maxDistSq{settings::perceptionRadius * settings::perceptionRadius};

    MathsVector<float, 3> forward{};
    // ATTENTION PEUT ETRE QUE isZero merde
    bool hasForward{forward.isZero(b.velocity.lengthSq())};
    if (!hasForward)
        forward = b.velocity.normalized();

    for (size_t j = 0; j < boids.getsize(); ++j) {
        if (j == index) continue;

        const Boid& other = boids[j];
        MathsVector<float, 3> toOther{other.position - b.position};
        float distSq{toOther.dot(toOther)};
        if (distSq > maxDistSq)
            continue;

        bool isThreaten{Species::canEat(other.specie, b.specie)};
        bool isHunting{Species::canEat(b.specie, other.specie)};
        bool sameSpecies{(other.specie == b.specie)};

        if (isThreaten) {
            predators.push_back(j);
            continue;
        }

        bool isNeighbor{sameSpecies || isHunting};
        if (!isNeighbor)
            continue;

        if (!hasForward) {
            neighbors.push_back(j);
            continue;
        }

        MathsVector<float, 3> dir{toOther.normalized()};
        if (forward.dot(dir) >= settings::cosVisionHalfAngle())
            neighbors.push_back(j);
    }
}



}
