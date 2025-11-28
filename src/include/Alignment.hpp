#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Alignment : public Rule {
public:
    float weight = 1.0f;

    Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const override;
};

}


#endif // ALIGNMENT_HPP
