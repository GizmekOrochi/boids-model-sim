#include "../../include/model/Flock.hpp"
#include <cmath>

namespace bd {

// Find neighbors within perception radius
DynamicArray<Boid> Flock::findNeighbors(size_t index) const {
    DynamicArray<Boid> neighbors;
    const Boid& b = boids[index];

    float maxDistSq = settings.visionRange * settings.visionRange;

    // convert vision angle to radians
    float visionAngleRad = settings.visionAngleDeg * (3.1415926f / 180.0f);

    // normalized forward direction of the boid
    Vec2<float> forward = b.velocity.normalized();

    for (size_t j = 0; j < boids.getsize(); ++j) {
        if (j == index) continue;

        const Boid& other = boids[j];

        Vec2<float> toNeighbor = other.position - b.position;
        float distSq = toNeighbor.x * toNeighbor.x + toNeighbor.y * toNeighbor.y;

        // distance check
        if (distSq > maxDistSq)
            continue;

        // if velocity is zero, treat as omnidirectional (rare)
        if (forward.length() < 0.001f) {
            neighbors.push_back(other);
            continue;
        }

        // angle check
        Vec2<float> dirToOther = toNeighbor.normalized();
        float dot = forward.dot(dirToOther); // cos(angle)

        // angle between them = acos(dot)
        // we check dot directly: dot > cos(maxAngle)
        float cosAngle = std::cos(visionAngleRad * 0.5f);

        if (dot >= cosAngle) {
            neighbors.push_back(other);
        }
    }

    return neighbors;
}


// Sum all rule-based forces
Vec2<float> Flock::computeRuleForces(const Boid& b, const DynamicArray<Boid>& neighbors) const {
    Vec2<float> total(0.0f, 0.0f);

    for (size_t i = 0; i < rules.getsize(); ++i) {
        Rule* r = rules[i];
        if (r)
            total += r->apply(b, neighbors);
    }

    return total;
}

// Enforce base speed when boid is alone
void Flock::enforceBaseSpeed(Boid& b, const DynamicArray<Boid>& neighbors) {
    if (neighbors.getsize() > 0) return;

    float vlen = b.velocity.length();

    // If frozen, choose random direction
    if (vlen < 0.0001f) {
        float angle = (float(rand()) / RAND_MAX) * 6.283185f;
        Vec2<float> dir(std::cos(angle), std::sin(angle));
        b.velocity = dir * settings.baseSpeed;
    }
    // If too slow, enforce minimum baseSpeed
    else if (vlen < settings.baseSpeed) {
        b.velocity = b.velocity.normalized() * settings.baseSpeed;
    }
}

// Limit acceleration
Vec2<float> Flock::clampAcceleration(const Vec2<float>& force) const {
    float len = force.length();
    if (len > settings.maxAcceleration && len > 0.0f)
        return force.normalized() * settings.maxAcceleration;
    return force;
}

// Limit velocity after adding force
Vec2<float> Flock::clampSpeed(const Vec2<float>& v) const {
    float len = v.length();
    if (len > settings.maxSpeed && len > 0.0f)
        return v.normalized() * settings.maxSpeed;
    return v;
}

// Move boid
void Flock::moveBoid(Boid& b) {
    b.position += b.velocity * settings.deltaTime;
}

// handling the bounces
void Flock::handleBoundaries(Boid& b) {
    if (b.position.x < 0.0f) { b.position.x = 0.0f; b.velocity.x *= -1; }
    if (b.position.x > settings.windowWidth) { b.position.x = settings.windowWidth; b.velocity.x *= -1; }

    if (b.position.y < 0.0f) { b.position.y = 0.0f; b.velocity.y *= -1; }
    if (b.position.y > settings.windowHeight) { b.position.y = settings.windowHeight; b.velocity.y *= -1; }
}

// Main function
void Flock::update() {
    size_t count = boids.getsize();
    if (count == 0) return;

    DynamicArray<Vec2<float>> nextVel;
    for (size_t i = 0; i < count; ++i)
        nextVel.push_back(Vec2<float>(0,0));

    // FIRST PASS: compute next velocities
    for (size_t i = 0; i < count; ++i) {
        Boid& b = boids[i];

        auto neighbors = findNeighbors(i);

        // rule forces
        Vec2<float> force = computeRuleForces(b, neighbors);

        // ensure minimum movement
        enforceBaseSpeed(b, neighbors);

        // limit acceleration
        force = clampAcceleration(force);

        // compute new velocity
        Vec2<float> newVel = b.velocity + force;

        // limit speed
        newVel = clampSpeed(newVel);

        nextVel[i] = newVel;
    }

    // SECOND PASS: apply velocities and move
    for (size_t i = 0; i < count; ++i) {
        boids[i].velocity = nextVel[i];

        moveBoid(boids[i]);
        handleBoundaries(boids[i]);
    }
}

}
