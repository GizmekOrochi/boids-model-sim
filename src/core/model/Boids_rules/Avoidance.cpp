#include "../../../include/model/Boids_rules/Avoidance.hpp"

namespace bd {

Vec3<float> Avoidance::apply(const Boid& b, const RuleContext& ctx) const{
    constexpr float wallMargin = 30.0f;
    constexpr float obstacleGain = 1.2f;
    constexpr float weight = 1.5f;
    constexpr float radius = 10.0f;

    Vec3<float> steer(0.f, 0.f, 0.f);

    //World boundaries
    if (b.position.x < wallMargin)
        steer.x += (wallMargin - b.position.x) / wallMargin;
    else if (b.position.x > settings::worldWidth - wallMargin)
        steer.x -= (b.position.x - (settings::worldWidth - wallMargin)) / wallMargin;

    if (b.position.y < wallMargin)
        steer.y += (wallMargin - b.position.y) / wallMargin;
    else if (b.position.y > settings::worldHeight - wallMargin)
        steer.y -= (b.position.y - (settings::worldHeight - wallMargin)) / wallMargin;

    if (b.position.z < wallMargin)
        steer.z += (wallMargin - b.position.z) / wallMargin;
    else if (b.position.z > settings::worldDeepth - wallMargin)
        steer.z -= (b.position.z - (settings::worldDeepth - wallMargin)) / wallMargin;

    // Obstacles
    for (size_t i = 0; i < ctx.obstacles.getsize(); ++i) {
        const Obstacle& o = ctx.obstacles[i];

        Vec3<float> diff = b.position - o.position;
        float distSq = diff.lengthSq();
        float minDist = radius + wallMargin;

        if (distSq < minDist * minDist && distSq > 1e-6f) {
            float dist = std::sqrt(distSq);
            Vec3<float> away = diff / dist;
            steer += away * (1.f - dist / minDist) * obstacleGain;
        }
    }

    if (steer.lengthSq() > 0.f)
        steer = steer.normalized();

    return steer * weight;
}

} // namespace