#ifndef RULE_HPP
#define RULE_HPP

#pragma once
#include "Vec2.hpp"
#include "DynamicArray.hpp"

namespace bd {

class Boid;

class Rule {
public:
    virtual ~Rule() = default;

    // Renvoie un vecteur représentant la force à appliquer au boid
    virtual Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const = 0;
};

} // namespace bd


#endif // RULE_HPP
