#include "../../../include/model/Boids_rules/Separation.hpp"

namespace bd {

MathsVector<float, 3> Separation::apply(const Boid& b, const RuleContext& ctx) const {
    MathsVector<float, 3> null{};
    if (ctx.neighbors.getsize() == 0)
        return null;

    for (size_t i = 0; i < ctx.neighbors.getsize(); ++i) {
        const Boid& n{ctx.boids[ctx.neighbors[i]]};

        MathsVector<float, 3> diff{b.position - n.position};
        float dist = diff.length();

        if (dist > 0.f)
            null += diff.normalized() / dist;
    }

    return null * settings::separationWeight;
}

} // namespace