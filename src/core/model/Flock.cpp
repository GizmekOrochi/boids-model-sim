#include "../../include/model/Flock.hpp"
#include <cmath>
#include <cstdlib>

namespace bd {

Vec3<float> Flock::computeRuleForces(const Boid& b, const DynamicArray<size_t>& neighbors,const DynamicArray<size_t>& predators) const {
    Vec3<float> total(0.f, 0.f, 0.f);

    RuleContext ctx {
        .boids = boids,
        .neighbors = neighbors,
        .predator = predators,
        .obstacles = obstacles
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

Vec3<float> Flock::clampAcceleration(const Vec3<float>& force) const {
    float len = force.length();
    if (len > settings::maxAcceleration && len > 0.f)
        return force.normalized() * settings::maxAcceleration;
    return force;
}

Vec3<float> Flock::clampSpeed(const Vec3<float>& v) const {
    float len = v.length();
    if (len > settings::maxSpeed && len > 0.f)
        return v.normalized() * settings::maxSpeed;
    return v;
}

DynamicArray<Vec3<float>> Flock::computeNextVelocities() {
    DynamicArray<Vec3<float>> nextVel;

    DynamicArray<size_t> neighbors;
    DynamicArray<size_t> predators;

    for (size_t i = 0; i < boids.getsize(); ++i) {
        Boid& b = boids[i];

        findNeighbors(i, neighbors, predators);

        Vec3<float> force = computeRuleForces(b, neighbors, predators);
        enforceBaseSpeed(b, neighbors);

        force = clampAcceleration(force);
        Vec3<float> v = clampSpeed(b.velocity + force);

        nextVel.push_back(v);
    }

    return nextVel;
}

void Flock::findNeighbors(size_t index, DynamicArray<size_t>& neighbors,DynamicArray<size_t>& predators) const {
    neighbors.clear();
    predators.clear();

    const Boid& b = boids[index];

    float maxDistSq = settings::perceptionRadius * settings::perceptionRadius;

    Vec3<float> forward(0.f, 0.f, 0.f);
    if (b.velocity.lengthSq() > 1e-6f)
        forward = b.velocity.normalized();

    for (size_t j = 0; j < boids.getsize(); ++j) {
        if (j == index) continue;

        const Boid& other = boids[j];

        Vec3<float> toNeighbor = other.position - b.position;
        float distSq = toNeighbor.dot(toNeighbor);
        if (distSq > maxDistSq)
            continue;

        bool isPredator = fear(b.specie, other.specie);
        bool isNeighbor = (other.specie == b.specie);

        if(!isNeighbor || !isPredator) continue;

        if (forward.lengthSq() < 1e-6f) {
            if (isNeighbor) neighbors.push_back(j);
            else if (isPredator) predators.push_back(j);
            continue;
        }

        Vec3<float> dir = toNeighbor.normalized();
        float dot = forward.dot(dir);

        if (dot >= settings::cosAngle) {
            if (isNeighbor) neighbors.push_back(j);
            else if (isPredator) predators.push_back(j);
        }
    }
}

}
