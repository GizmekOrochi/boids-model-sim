#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

#pragma once
#include "Rule.hpp"

namespace bd {


class Alignment : public Rule {
public:

    MathsVector<float, 3> apply(const Boid& b, const RuleContext& ctx) const override;
};

} //namepace


#endif // ALIGNMENT_HPP