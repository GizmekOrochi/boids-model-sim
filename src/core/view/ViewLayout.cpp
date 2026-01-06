#include "../../include/view/ViewLayout.hpp"

namespace bd {

void ViewLayout::build() {
    buttons.clear();
    sliders.clear();

    buttons.push_back({"Save", UiAction::Save, {20,20}, {120,30}});
    buttons.push_back({"Load", UiAction::Load, {160,20}, {120,30}});
    buttons.push_back({"Add Boid", UiAction::AddBoid, {20,540}, {70,30}});
    buttons.push_back({"Rm Boid", UiAction::RmBoid, {100,540}, {70,30}});
    buttons.push_back({"Add Obs", UiAction::AddObstacle, {20,490}, {70,30}});
    buttons.push_back({"Rm Obs", UiAction::RmObstacle, {100,490}, {70,30}});


    float startY = 80.f;
    float gap = 50.f;

    auto add = [&](const char* name, float* v, float min, float max, int i) {
        sliders.push_back({name, v, min, max, {20.f, startY + i * gap}, 240.f});
    };

    int i = 0;
    add("Cohesion", &settings::cohesionWeight, 0.0f, 1.0f, i++);
    add("Separation", &settings::separationWeight, 0.0f, 1.0f, i++);
    add("Alignment", &settings::alignmentWeight, 0.0f, 1.0f, i++);
    add("Perception", &settings::perceptionRadius, 10.0f, 100.0f, i++);
    add("Sep Dist", &settings::separationDistance, 5.0f, 50.0f, i++);
    add("Vision Angle", &settings::visionAngleDeg, 0.0f, 360.f, i++);
    add("flow", &settings::visionAngleDeg, 0.0f, 360.f, i++);


}

}
