#include "../../include/model/World.hpp"

namespace bd {

void World::handleBoundaries(Boid& b) const {
    // X axis
    if (b.position[0] < 0.0f) {
        b.position[0] = 0.0f;
        b.velocity[0] *= -1.0f;
    }
    else if (b.position[0] > getWidth()) {
        b.position[0] = getWidth();
        b.velocity[0] *= -1.0f;
    }

    // Y axis
    if (b.position[1] < 0.0f) {
        b.position[1] = 0.0f;
        b.velocity[1] *= -1.0f;
    }
    else if (b.position[1] > getHeight()) {
        b.position[1] = getHeight();
        b.velocity[1] *= -1.0f;
    }

    // Z axis
    if (b.position[2] < 0.0f) {
        b.position[2] = 0.0f;
        b.velocity[2] *= -1.0f;
    }
    else if (b.position[2] > getDepth()) {
        b.position[2] = getDepth();
        b.velocity[2] *= -1.f;
    }
}

}
