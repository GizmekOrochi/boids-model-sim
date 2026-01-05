#include "../../include/model/World.hpp"

namespace bd {

World::World(float w, float h, float d)
    : width(w), height(h), depth(d)
{}

void World::handleBoundaries(Boid& b) const {
    // X axis
    if (b.position.x < 0.f) {
        b.position.x = 0.f;
        b.velocity.x *= -1.f;
    }
    else if (b.position.x > width) {
        b.position.x = width;
        b.velocity.x *= -1.f;
    }

    // Y axis
    if (b.position.y < 0.f) {
        b.position.y = 0.f;
        b.velocity.y *= -1.f;
    }
    else if (b.position.y > height) {
        b.position.y = height;
        b.velocity.y *= -1.f;
    }

    // Z axis
    if (b.position.z < 0.f) {
        b.position.z = 0.f;
        b.velocity.z *= -1.f;
    }
    else if (b.position.z > depth) {
        b.position.z = depth;
        b.velocity.z *= -1.f;
    }
}

}
