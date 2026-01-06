#ifndef AVOIDANCE_HPP
#define AVOIDANCE_HPP

#pragma once
#include "Rule.hpp"
#include "../utils/Vec3.hpp"
#include "../../config/Settings.hpp"

namespace bd {

class Avoidance : public Rule {
public:
    Vec3<float> apply(const Boid& b,const DynamicArray<size_t>& neighbors, const DynamicArray<Boid>& boids) const override;
};

}


#endif // AVOIDANCE_HPP
