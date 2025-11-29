#ifndef COHESION_HPP
#define COHESION_HPP

#pragma once
#include "Rule.hpp"
#include "Vec2.hpp"

namespace bd {

class Cohesion : public Rule {
public:
    float weight = 1.0f;

    Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const override;
};

}

#endif // COHESION_HPP
