#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

#pragma once
#include "Rule.hpp"
#include "../utils/Vec3.hpp"
#include "../../config/Settings.hpp"

namespace bd {

class Alignment : public Rule {
public:
    float weight = settings::alignmentWeight;

    Vec3<float> apply(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<Boid>& boids) const override;
};

}


#endif // ALIGNMENT_HPP
