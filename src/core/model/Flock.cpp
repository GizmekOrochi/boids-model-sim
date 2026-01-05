#include "../../include/model/Flock.hpp"
#include <cmath>

namespace bd {

    /*
DynamicArray<Boid> Flock::findNeighbors(size_t index) const {
    DynamicArray<Boid> neighbors;
    const Boid& b = boids[index];

    float maxDistSq = settings.visionRange * settings.visionRange;
    float visionAngleRad = settings.visionAngleDeg * (3.1415926f / 180.0f);

    Vec2<float> forward = b.velocity.normalized();

    for (size_t j = 0; j < boids.getsize(); ++j) {
        if (j == index) continue;

        const Boid& other = boids[j];
        Vec2<float> toNeighbor = other.position - b.position;

        float distSq = toNeighbor.dot(toNeighbor);
        if (distSq > maxDistSq)
            continue;

        if (forward.length() < 0.001f) {
            neighbors.push_back(other);
            continue;
        }

        Vec2<float> dir = toNeighbor.normalized();
        float dot = forward.dot(dir);
        float cosAngle = std::cos(visionAngleRad * 0.5f);

        if (dot >= cosAngle)
            neighbors.push_back(other);
    }

    return neighbors;
}

*/

Vec2<float> Flock::computeRuleForces(const Boid& b, const DynamicArray<Boid>& neighbors) const {
    Vec2<float> total(0.0f, 0.0f);

    for (size_t i = 0; i < rules.getsize(); ++i)
        if (rules[i])
            total += rules[i]->apply(b, neighbors);

    return total;
}

void Flock::enforceBaseSpeed(Boid& b, const DynamicArray<Boid>& neighbors) {
    if (neighbors.getsize() > 0)
        return;

    float len = b.velocity.length();

    if (len < 0.0001f) {
        float a = (float(rand()) / RAND_MAX) * 6.283185f;
        b.velocity = Vec2<float>(std::cos(a), std::sin(a))
                   * settings.baseSpeed;
    }
    else if (len < settings.baseSpeed) {
        b.velocity = b.velocity.normalized() * settings.baseSpeed;
    }
}

Vec2<float> Flock::clampAcceleration(const Vec2<float>& force) const {
    float len = force.length();
    if (len > settings.maxAcceleration && len > 0.0f)
        return force.normalized() * settings.maxAcceleration;
    return force;
}

Vec2<float> Flock::clampSpeed(const Vec2<float>& v) const {
    float len = v.length();
    if (len > settings.maxSpeed && len > 0.0f)
        return v.normalized() * settings.maxSpeed;
    return v;
}

DynamicArray<Vec2<float>> Flock::computeNextVelocities() {
    DynamicArray<Vec2<float>> nextVel;

    for (size_t i = 0; i < boids.getsize(); ++i) {
        Boid& b = boids[i];
        auto neighbors = findNeighbors(i);

        Vec2<float> force = computeRuleForces(b, neighbors);
        enforceBaseSpeed(b, neighbors);
        force = clampAcceleration(force);

        Vec2<float> v = clampSpeed(b.velocity + force);
        nextVel.push_back(v);
    }

    return nextVel;
}


DynamicArray<Boid> Flock::findNeighbors(size_t index) const {
    DynamicArray<Boid> neighbors;
    const Boid& b = boids[index];

    float maxDistSq = settings.visionRange * settings.visionRange;
    float visionAngleRad = settings.visionAngleDeg * (3.1415926f / 180.0f);

    Vec2<float> forward = b.velocity.normalized();

    for (size_t j = 0; j < boids.getsize(); ++j) {
        if (j == index) continue;

        const Boid& other = boids[j];
        Vec2<float> toNeighbor = other.position - b.position;

        float distSq = toNeighbor.dot(toNeighbor);
        if (distSq > maxDistSq)
            continue;

        if (forward.length() < 0.001f) {
            neighbors.push_back(other);
            continue;
        }

        Vec2<float> dir = toNeighbor.normalized();
        float dot = forward.dot(dir);
        float cosAngle = std::cos(visionAngleRad * 0.5f);

        if (dot >= cosAngle)
            neighbors.push_back(other);
    }

    return neighbors;
}


}
