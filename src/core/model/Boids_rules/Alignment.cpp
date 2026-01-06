#include "../../../include/model/Boids_rules/Alignment.hpp"

namespace bd {

Vec3<float> Alignment::apply(const Boid& b, const RuleContext& ctx) const {
    if (ctx.neighbors.getsize() == 0)
        return Vec3<float>(0.f, 0.f, 0.f);

    Vec3<float> avgVel(0.f, 0.f, 0.f);

    for (size_t i = 0; i < ctx.neighbors.getsize(); ++i) {
        avgVel += ctx.boids[ctx.neighbors[i]].velocity;
    }

    avgVel /= static_cast<float>(ctx.neighbors.getsize());

    Vec3<float> steer = avgVel - b.velocity;
    return steer * weight;
}

}
