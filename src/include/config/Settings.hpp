#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#pragma once
#include <cmath>

namespace bd::settings {

// Window // ui
//boids window
inline float windowWidth  = 800.0f;
inline float windowHeight = 600.0f;
inline float windowDeepth = 600.0f;
//menu size
inline float panelWidth = 300.f;

inline int nbboid = 200;

// Physics
inline float baseSpeed = 1.0f;

inline float maxSpeed = 4.0f;
inline float maxAcceleration = 0.1f;
inline float deltaTime = 1.0f;

inline float cohesionWeight = 0.01f;  // PUT 0.01f after
inline float separationWeight = 1.0f; // PUT 1.0f after
inline float desiredDistance = 20.0f;
inline float alignmentWeight = 0.125f;
inline float separationDistance = 15.0f;

// Boids perception
inline float perceptionRadius = 50.0f;

// Boids vision angle
inline float visionAngleDeg = 180.0f;

// Derived values
inline float visionAngleRad = visionAngleDeg * (3.1415926535f / 180.0f);
inline float cosAngle = std::cos(visionAngleRad * 0.5f);

} // namespace bd and settings

#endif
