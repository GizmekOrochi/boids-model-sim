#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#pragma once
#include "Rule.hpp"
#include "../utils/Vec2.hpp"
#include "../../config/Settings.hpp"

namespace bd {

class Separation : public Rule {
private:
    Settings settings;
public:
    float desiredDistance = settings.desiredDistance;
    float weight = settings.separationweight;

    Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const override;
};

}


#endif // SEPARATION_HPP
