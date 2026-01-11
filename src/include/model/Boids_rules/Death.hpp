#ifndef DEATH_HPP
#define DEATH_HPP

#include "Rule.hpp"

namespace bd {

class Death : public Rule {
    public:

        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const override;
    };

} // namespace bd

#endif // DEATH_HPP