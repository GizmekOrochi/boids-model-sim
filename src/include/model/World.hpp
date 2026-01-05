#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once
#include "Boid.hpp"

namespace bd {

class World {
public:
    World(float w, float h, float d);

    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getDepth() const { return depth; }

    void handleBoundaries(Boid& b) const;

private:
    float width;
    float height;
    float depth;
};

}

#endif // WORLD_HPP
