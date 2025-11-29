#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#pragma once

namespace bd {

class Settings {
public:
    // Window
    float windowWidth  = 800.0f;
    float windowHeight = 600.0f;

    // Physics
    float baseSpeed        = 1.0f;   // basespeed

    float maxSpeed        = 4.0f;   // vmax
    float maxAcceleration = 0.1f;   // amax
    float deltaTime       = 1.0f;   // delta

    // Boids vision range
    float visionAngleDeg = 360.0f;   // default: half circle
    float visionRange    = 100.0f;    // default: same as perceptionRadius
    
    // Boids perception
    float perceptionRadius = 100.0f; // r
    float separationDistance = 20.0f; // dmin

    Settings() = default;
};

}

#endif
