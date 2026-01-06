#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#pragma once
#include <cmath>

namespace bd::settings {

// Window // ui
//boids window
inline float windowWidth  = 800.0f;
inline float windowHeight = 600.0f;

// Camera
inline float moveSpeed = 250.0f;
inline float rotSpeed = 1.6f;

//menu size
inline float panelWidth = 300.f;

// Physics
inline float worldWidth  = windowWidth;
inline float worldHeight = windowHeight;
inline float worldDeepth = 600.0f;

//Boid number
inline int nbboid = 10;

//obstacle number
inline int nbobstacle = 0;

// Speed
inline float baseSpeed = 1.0f;
inline float maxSpeed = 4.0f;
inline float maxAcceleration = 0.1f;
inline float deltaTime = 1.0f;

// Rules Weight
inline float cohesionWeight = 0.01f;
inline float separationWeight = 1.0f;
inline float desiredDistance = 20.0f;
inline float alignmentWeight = 0.125f;
inline float separationDistance = 15.0f;

// Boids perception / vision
inline float perceptionRadius = 50.0f;
inline float visionAngleDeg = 180.0f;

// Derived values
inline float visionAngleRad = visionAngleDeg * (3.1415926535f / 180.0f);
inline float cosAngle = std::cos(visionAngleRad * 0.5f);

} // namespace bd and settings

#endif
