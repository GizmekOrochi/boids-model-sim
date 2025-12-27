#include "include/Simulation.hpp"
#include "include/config/Settings.hpp"

int main() {
    bd::Settings settings;
    bd::Simulation sim;
    sim.run(settings);
}