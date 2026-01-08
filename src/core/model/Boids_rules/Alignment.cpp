#include "../../../include/model/Boids_rules/Alignment.hpp"

namespace bd {

MathsVector<float, 3> Alignment::apply(const Boid& b, const RuleContext& ctx) const {
    MathsVector<float, 3> null{};
    if (ctx.neighbors.getsize() == 0)
        return null;
;

    for (size_t i = 0; i < ctx.neighbors.getsize(); ++i) {
        null += ctx.boids[ctx.neighbors[i]].velocity;
    }

    null /= static_cast<float>(ctx.neighbors.getsize());

    MathsVector<float, 3> steer{null - b.velocity};
    return steer * settings::alignmentWeight;
}

} //namepace
