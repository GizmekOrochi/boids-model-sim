#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#pragma once

namespace bd {

class Settings {
public:
    // Window
    float windowWidth = 800.0f;
    float windowHeight = 600.0f;

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

    // Boids perception
    float perceptionRadius = 50.0f; // r
    
    // Boids vision range
    float visionAngleDeg = 90.0f; // default: half circle
    float visionRange = 50.0f; // default: same as perceptionRadius

    Settings() = default;
};

}

#endif
