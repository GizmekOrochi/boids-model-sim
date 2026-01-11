#ifndef BOID_HPP
#define BOID_HPP

#pragma once
#include "utils/Vec3.hpp"
#include "utils/Species.hpp"
#include "../config/Settings.hpp"

namespace bd {

    class Boid {
    public:

        Vec3<float> position;
        Vec3<float> velocity;

        Species::BoidSpecies specie;

        int ID;

        Boid(Species::BoidSpecies specie) : position(0.0f,0.0f,0.0f), velocity(0.0f,0.0f,0.0f), specie(specie), ID(settings::currentIDAvalible) {
            settings::currentIDAvalible++;
        }

        Boid(float x, float y, float z, Species::BoidSpecies specie) : position(x,y,z), velocity(0.0f,0.0f,0.0f), specie(specie), ID(settings::currentIDAvalible) {
            settings::currentIDAvalible++;
        }

        ~Boid() { settings::currentIDAvalible--; }
    };

}

#endif // BOID_HPP