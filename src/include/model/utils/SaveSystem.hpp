#ifndef SAVESYSTEM_HPP
#define SAVESYSTEM_HPP

#include <string>

#include "../Simulation.hpp"

namespace bd {

/**
 * @brief Handles serialization and deserialization of simulation state.
 *
 * The SaveSystem class provides static functions to persist and restore
 * the state of a Simulation. It is responsible for saving and loading
 * world dimensions and boid state (position and orientation) to and from
 * an external file.
 */
class SaveSystem {
public:
    /**
     * @brief Saves the current simulation state to a file.
     *
     * This function writes the world dimensions and the list of boids
     * (including their positions and normalized velocity directions)
     * to the specified file.
     *
     * @param simulation The simulation to save.
     * @param filename Path to the output file.
     * @return True if the save operation succeeded, false otherwise.
     */
    static bool save(const Simulation& simulation, const std::string& filename);

    /**
     * @brief Loads a simulation state from a file.
     *
     * This function reads world dimensions and boid data from the
     * specified file and reconstructs the simulation state.
     *
     * @param simulation The simulation to modify with loaded data.
     * @param filename Path to the input file.
     * @return True if the load operation succeeded, false otherwise.
     */
    static bool load(Simulation& simulation, const std::string& filename);
};

}

#endif
