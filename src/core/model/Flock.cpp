#include "../../include/model/Flock.hpp"
#include <cmath>
#include <cstdlib>

namespace bd {

Vec3<float> Flock::computeRuleForces(const Boid& b, const DynamicArray<size_t>& neighbors,const DynamicArray<size_t>& predators, DynamicArray<int>* eaten) const {
    Vec3<float> total(0.f, 0.f, 0.f);

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
        float phi   = float(rand()) / RAND_MAX * 3.1415926f;

        b.velocity = Vec3<float>(std::sin(phi) * std::cos(theta), std::sin(phi) * std::sin(theta),std::cos(phi)) * settings::baseSpeed;
    }
    else if (len < settings::baseSpeed) {
        b.velocity = b.velocity.normalized() * settings::baseSpeed;
    }
}

Vec3<float> Flock::clampAcceleration(const Vec3<float>& force, float hungeraccleration) const {
    float maxAcc = settings::maxAcceleration;

    float len = force.length();
    if (len > maxAcc && len > 0.f)
        return force.normalized() * maxAcc;

    return force * hungeraccleration;
}


Vec3<float> Flock::clampSpeed(const Vec3<float>& force) const{
    float maxSpeed = settings::maxSpeed;

    float len = force.length();
    if (len > maxSpeed && len > 0.f)
        return force.normalized() * maxSpeed;

    return force;
}

DynamicArray<Vec3<float>> Flock::computeNextVelocities(DynamicArray<int>* eaten) {
    DynamicArray<Vec3<float>> nextVel;

    DynamicArray<size_t> neighbors;
    DynamicArray<size_t> predators;

    for (size_t i = 0; i < boids.getsize(); ++i) {
        Boid& b = boids[i];

        findNeighbors(i, neighbors, predators);

        Vec3<float> force = computeRuleForces(b, neighbors, predators, eaten);
        enforceBaseSpeed(b, neighbors);

        // Predator prey hunger boost
        float hungeraccleration = static_cast<float>(speciesTier(b.specie));

        force = clampAcceleration(force, hungeraccleration);
        Vec3<float> v = clampSpeed(b.velocity + force);

        nextVel.push_back(v);
    }

    return nextVel;
}

void Flock::findNeighbors(size_t index, DynamicArray<size_t>& neighbors, DynamicArray<size_t>& predators) const{
    neighbors.clear();
    predators.clear();

    const Boid& b = boids[index];
    const float maxDistSq =
        settings::perceptionRadius * settings::perceptionRadius;

    Vec3<float> forward{};
    bool hasForward = b.velocity.lengthSq() > 1e-6f;
    if (hasForward)
        forward = b.velocity.normalized();

    for (size_t j = 0; j < boids.getsize(); ++j) {
        if (j == index) continue;

        const Boid& other = boids[j];

        Vec3<float> toOther = other.position - b.position;
        float distSq = toOther.dot(toOther);
        if (distSq > maxDistSq)
            continue;

        bool isThreaten = canEat(other.specie, b.specie);
        bool isHunting = canEat(b.specie, other.specie);
        bool sameSpecies  = (other.specie == b.specie);

        if (isThreaten) {
            predators.push_back(j);
            continue;
        }

        bool isNeighbor = sameSpecies || isHunting;
        if (!isNeighbor)
            continue;

        if (!hasForward) {
            neighbors.push_back(j);
            continue;
        }

        Vec3<float> dir = toOther.normalized();
        if (forward.dot(dir) >= settings::cosAngle)
            neighbors.push_back(j);
    }
}



}
