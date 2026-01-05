#ifndef RULE_HPP
#define RULE_HPP

#pragma once
#include "../utils/Vec3.hpp"
#include "../utils/DynamicArray.hpp"

namespace bd {

class Boid;

class Rule {
public:
    virtual ~Rule() = default;

    // Renvoie un vecteur représentant la force à appliquer au boid
    virtual Vec3<float> apply(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<Boid>& boids) const = 0;

};

}


#endif // RULE_HPP
