#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Separation : public Rule {
public:
    float desiredDistance = 20.f;
    float weight = 1.0f;

    Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const override;
};

}


#endif // SEPARATION_HPP
