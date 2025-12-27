#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#pragma once

namespace bd {

class Settings {
public:
    // Window boids
    static int constexpr windowWidth  = 800;
    static int constexpr windowHeight = 600;

    // Window setting
    static int constexpr windowSetWidth  = 200;
    static int constexpr windowSetHeight = windowHeight;

    // Global window size
    static int constexpr fullwindowWidth = windowWidth + windowSetWidth;
    static int constexpr fullwindowHeight = windowHeight;

    // Physics
    float baseSpeed = 1.0f; // basespeed

    float maxSpeed = 4.0f; // vmax
    float maxAcceleration = 0.1f; // amax
    float deltaTime = 1.0f; // delta

    float cohesionweight = 0.01f; // CohesionWeight
    float separationweight = 1.0f; // SeparationWeight
    float desiredDistance = 20.0f; // distance min between each boids
    float alignmentweight = 0.125f; // AlignmentWeight
    float separationDistance = 15.0f; // dmin

    // Boids vision range
    float visionAngleDeg = 90.0f; // default: half circle
    float visionRange = 50.0f; // default: same as perceptionRadius

    // Boids perception
    float perceptionRadius = 50.0f; // r

    Settings() = default;
};

}

#endif
