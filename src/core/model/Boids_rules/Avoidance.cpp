#include "../../../include/model/Boids_rules/Avoidance.hpp"
#include "../../../include/model/Boid.hpp"

namespace bd {

Vec3<float> Avoidance::apply(const Boid& b, const DynamicArray<size_t>&, const DynamicArray<Boid>&) const{
    constexpr float margin = 30.0f;
    constexpr float weight = 1.5f;

    Vec3<float> steer(0.f, 0.f, 0.f);

    // --- X axis ---
    if (b.position.x < margin)
        steer.x += (margin - b.position.x) / margin;
    else if (b.position.x > settings::worldWidth - margin)
        steer.x -= (b.position.x - (settings::worldWidth - margin)) / margin;

    // --- Y axis ---
    if (b.position.y < margin)
        steer.y += (margin - b.position.y) / margin;
    else if (b.position.y > settings::worldHeight - margin)
        steer.y -= (b.position.y - (settings::worldHeight - margin)) / margin;

    // --- Z axis ---
    if (b.position.z < margin)
        steer.z += (margin - b.position.z) / margin;
    else if (b.position.z > settings::worldDeepth - margin)
        steer.z -= (b.position.z - (settings::worldDeepth - margin)) / margin;

    if (steer.lengthSq() > 0.f)
        steer = steer.normalized();

    return steer * weight;
}

}
