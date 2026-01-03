#include "../../include/model/World.hpp"

namespace bd {

World::World(float w, float h) : width(w), height(h) {}

float World::getWidth() const {
    return width;
}

float World::getHeight() const {
    return height;
}

void World::handleBoundaries(Boid& b) const {
    if (b.position.x < 0.0f) {
        b.position.x = 0.0f;
        b.velocity.x *= -1.0f;
    }
    if (b.position.x > width) {
        b.position.x = width;
        b.velocity.x *= -1.0f;
    }

    if (b.position.y < 0.0f) {
        b.position.y = 0.0f;
        b.velocity.y *= -1.0f;
    }
    if (b.position.y > height) {
        b.position.y = height;
        b.velocity.y *= -1.0f;
    }
}

}
