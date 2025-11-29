#include "../../include/model/Alignment.hpp"
#include "../../include/model/Vec2.hpp"
#include "../../include/model/Boid.hpp"


namespace bd {

Vec2<float> Alignment::apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const {
    size_t count = neighbors.getsize();
    if (count == 0) {
        return Vec2<float>(0.0f, 0.0f);
    }

    Vec2<float> avgVelocity(0.0f, 0.0f);
    for (size_t i = 0; i < count; ++i) {
        avgVelocity += neighbors[i].velocity;
    }
    avgVelocity /= static_cast<float>(count);

    // steer toward the average velocity
    Vec2<float> steering = avgVelocity - boid.velocity;
    return steering * weight;
}

}