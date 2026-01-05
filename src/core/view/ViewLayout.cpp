#include "../../include/view/ViewLayout.hpp"

namespace bd {

void ViewLayout::build(Settings& s) {
    buttons.clear();
    sliders.clear();

    buttons.push_back({"Save", UiAction::Save, {20,20}, {120,30}});
    buttons.push_back({"Load", UiAction::Load, {160,20}, {120,30}});
    buttons.push_back({"Add Boid", UiAction::AddBoid, {20,540}, {120,30}});
    buttons.push_back({"Rm Boid", UiAction::RmBoid, {160,540}, {120,30}});

    float startY = 80.f;
    float gap = 60.f;

    auto add = [&](const char* name, float* v, float min, float max, int i) {
        sliders.push_back({name, v, min, max, {20.f, startY + i * gap}, 240.f});
    };

    int i = 0;
    add("Cohesion", &s.cohesionweight, 0.f, 0.1f, i++);
    add("Separation", &s.separationweight, 0.f, 5.f, i++);
    add("Alignment", &s.alignmentweight, 0.f, 0.5f, i++);
    add("Perception", &s.perceptionRadius, 10.f, 200.f, i++);
    add("Max Accel", &s.maxAcceleration, 0.01f, 1.f, i++);
    add("Sep Dist", &s.separationDistance, 5.f, 100.f, i++);
    add("Max Speed", &s.maxSpeed, 1.f, 10.f, i++);
    add("Vision Angle", &s.visionAngleDeg, 5.f, 360.f, i++);
}

}
