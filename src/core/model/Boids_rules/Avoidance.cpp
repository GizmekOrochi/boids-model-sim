#include "../../../include/model/Boids_rules/Avoidance.hpp"

namespace bd {

constexpr float wallMargin = 30.0f;
constexpr float obstacleGain = 1.2f;
constexpr float predatorGain = 2.5f;
constexpr float weight = 1.5f;
constexpr float radius = 10.0f;

Vec3<float> Avoidance::apply(const Boid& b, const RuleContext& ctx) const {
    Vec3<float> steer(0.f, 0.f, 0.f);

    steer += avoidWorldBounds(b);
    steer += avoidObstacles(b, ctx);
    steer += avoidPredators(b, ctx);

    if (steer.lengthSq() > 0.f)
        return steer.normalized() * weight;
    return steer;
}


Vec3<float> Avoidance::avoidWorldBounds(const Boid& b) const {
    Vec3<float> steer(0.f, 0.f, 0.f);

    // X
    if (b.position.x < wallMargin)
        steer.x += (wallMargin - b.position.x) / wallMargin;
    else if (b.position.x > settings::worldWidth - wallMargin)
        steer.x -= (b.position.x - (settings::worldWidth - wallMargin)) / wallMargin;

    // Y
    if (b.position.y < wallMargin)
        steer.y += (wallMargin - b.position.y) / wallMargin;
    else if (b.position.y > settings::worldHeight - wallMargin)
        steer.y -= (b.position.y - (settings::worldHeight - wallMargin)) / wallMargin;

    // Z
    if (b.position.z < wallMargin)
        steer.z += (wallMargin - b.position.z) / wallMargin;
    else if (b.position.z > settings::worldDeepth - wallMargin)
        steer.z -= (b.position.z - (settings::worldDeepth - wallMargin)) / wallMargin;

    return steer;
}

Vec3<float> Avoidance::avoidObstacles(const Boid& b, const RuleContext& ctx) const {
    Vec3<float> steer(0.f, 0.f, 0.f);
    const float minDist = radius + wallMargin;

    for (size_t i = 0; i < ctx.obstacles.getsize(); ++i) {
        const Obstacle& obs = ctx.obstacles[i];

        const float hx = obs.sizeX * 0.5f;
        const float hy = obs.sizeY * 0.5f;
        const float hz = obs.sizeZ * 0.5f;

        Vec3<float> closest {
            std::max(obs.position.x - hx, std::min(b.position.x, obs.position.x + hx)),
            std::max(obs.position.y - hy, std::min(b.position.y, obs.position.y + hy)),
            std::max(obs.position.z - hz, std::min(b.position.z, obs.position.z + hz))
        };

        Vec3<float> diff = b.position - closest;
        float distSq = diff.lengthSq();

        if (distSq < minDist * minDist && distSq > 1e-6f) {
            float dist = std::sqrt(distSq);
            Vec3<float> away = diff / dist;
            steer += away * (1.f - dist / minDist) * obstacleGain;
        }
    }

    return steer;
}

Vec3<float> Avoidance::avoidPredators(const Boid& b, const RuleContext& ctx) const {
    Vec3<float> steer(0.f, 0.f, 0.f);
    const float perceptionSq = settings::perceptionRadius * settings::perceptionRadius;

    for (size_t i = 0; i < ctx.predator.getsize(); ++i) {
        const Boid& predator = ctx.boids[ctx.predator[i]];

        Vec3<float> diff = b.position - predator.position;
        float distSq = diff.lengthSq();

        if (distSq < perceptionSq && distSq > 1e-6f) {
            float dist = std::sqrt(distSq);
            Vec3<float> away = diff / dist;
            float strength = 1.f - dist / settings::perceptionRadius;
            steer += away * strength * predatorGain;
        }
    }

    return steer;
}

} // namespace bd
