#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once
#include "Boid.hpp"
#include "../config/Settings.hpp"

namespace bd {

class World {
public:

    World() = default;

    World(float w, float h, float d) : width(w), height(h), depth(d) {}

    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getDepth() const { return depth; }

    void handleBoundaries(Boid& b) const;

private:
    float width = settings::worldWidth;
    float height = settings::worldHeight;
    float depth = settings::worldDeepth;
};

} // namespace

#endif // WORLD_HPP