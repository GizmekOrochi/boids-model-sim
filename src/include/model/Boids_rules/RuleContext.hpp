#ifndef RULECONTEXT_HPP
#define RULECONTEXT_HPP

#include "Rule.hpp"
#include "../utils/Vec3.hpp"
#include "../utils/DynamicArray.hpp"
#include "../Obstacle.hpp"
#include "../Boid.hpp"
#include "../utils/Vec3.hpp"
#include "../../config/Settings.hpp"

namespace bd {

struct RuleContext {
    const DynamicArray<Boid>& boids;
    const DynamicArray<size_t>& neighbors;
    const DynamicArray<size_t>& predator;
    const DynamicArray<Obstacle>& obstacles;
    DynamicArray<int>* eaten;
};

} // namespace

#endif