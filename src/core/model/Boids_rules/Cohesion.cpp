#include "../../../include/model/Boids_rules/Cohesion.hpp"

namespace bd {

Vec3<float> Cohesion::apply(const Boid& b, const RuleContext& ctx) const {
    if (ctx.neighbors.getsize() == 0)
        return Vec3<float>(0.f, 0.f, 0.f);

    Vec3<float> center(0.f, 0.f, 0.f);

    for (size_t i = 0; i < ctx.neighbors.getsize(); ++i) {
        center += ctx.boids[ctx.neighbors[i]].position;
    }

    center /= static_cast<float>(ctx.neighbors.getsize());

    Vec3<float> steer = center - b.position;
    return steer * weight;
}

} // namespace
