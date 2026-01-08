#ifndef SAVESYSTEM_HPP
#define SAVESYSTEM_HPP

#include <string>

#pragma once
#include "../Simulation.hpp"

namespace bd {

    class SaveSystem {
    public:

        static bool save(const Simulation& simulation, const std::string& filename);
        static bool load(Simulation& simulation, const std::string& filename);
    };

}

#endif