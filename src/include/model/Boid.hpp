#ifndef BOID_HPP
#define BOID_HPP

#pragma once
#include "utils/MathsVector.hpp"
#include "utils/Species.hpp"
#include "../config/Settings.hpp"

namespace bd {

    class Boid {
    public:

        MathsVector<float, 3> position;
        MathsVector<float, 3> velocity;
        Species::BoidSpecies specie;
        int ID;

        Boid(Species::BoidSpecies specie) : position{}, velocity{}, specie(specie), ID{settings::currentIDAvalible} { settings::currentIDAvalible++; }

        Boid(MathsVector<float, 3> position, Species::BoidSpecies specie) : position{position}, velocity{}, specie{specie}, ID{settings::currentIDAvalible} {
            settings::currentIDAvalible++;
        }

        ~Boid() { settings::currentIDAvalible--; }
    };

} //nanespace

#endif // BOID_HPP