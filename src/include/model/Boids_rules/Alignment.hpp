#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

#pragma once
#include "Rule.hpp"
#include "../utils/Vec2.hpp"
#include "../../config/Settings.hpp"

namespace bd {

class Alignment : public Rule {
public:
    float weight = settings::alignmentWeight;

    Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const override;
};

}


#endif // ALIGNMENT_HPP
