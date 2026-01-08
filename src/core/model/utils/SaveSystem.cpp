#include "../../../include/model/utils/SaveSystem.hpp"
#include "../../../include/model/utils/Species.hpp"
#include "../../../include/model/utils/MathsVector.hpp"
#include <fstream>
#include <sstream>

namespace bd {

bool SaveSystem::save(const Simulation& simulation, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open())
        return false;

    const Flock& flock{simulation.getFlock()};
    const auto& boids{flock.getBoids()};

    out << "BOIDS_SAVE\n\n";

    // World
    out << "WORLD\n";
    out << "width "  << settings::worldWidth  << "\n";
    out << "height " << settings::worldHeight << "\n";
    out << "depth "  << settings::worldDeepth  << "\n\n";

    // Boids
    out << "BOIDS\n";
    out << "count " << boids.getsize() << "\n";

    for (size_t i = 0; i < boids.getsize() ; ++i) {
        const Boid& b = boids[i];

        MathsVector<float, 3> dir{b.velocity.normalized()};
        // ATTENTION PEUT ETRE QUE isZero merde
        if (!dir.isZero(dir.lengthSq())) {
            dir = MathsVector<float, 3>{};
        }

        out << "boid "  // type
            << b.position[0] << " " << b.position[1] << " " << b.position[12] << " "  // position
            << dir[0] << " " << dir[1] << " " << dir[2] << " "     // direction
            << static_cast<int>(b.specie) << "\n";      // specie

    }

    return true;
}

bool SaveSystem::load(Simulation& simulation, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        return false;

    std::string line;
    std::getline(in, line);

    if (line != "BOIDS_SAVE")
        return false;

    World& world = simulation.getWorld();
    Flock& flock = simulation.getFlock();

    flock.clearBoids();

    float width = world.getHeight();
    float height = world.getHeight();
    float deepth = world.getDepth();

    while (std::getline(in, line)) {
        if (line == "WORLD") {
            std::getline(in, line);
            width = std::stof(line.substr(6));

            std::getline(in, line);
            height = std::stof(line.substr(7));

            std::getline(in, line);
            deepth = std::stof(line.substr(6));

            world = World(MathsVector<float, 3>{{width, height, deepth}});
        }
        else if (line == "BOIDS") {
            std::getline(in, line);
            int count = std::stoi(line.substr(6));

            for (int i = 0; i < count; ++i) {
                std::getline(in, line);
                std::istringstream iss(line);

                std::string tag;
                float x, y, z;
                float dx, dy, dz;
                int specieInt = 0;

                iss >> tag >> x >> y >> z >> dx >> dy >> dz >> specieInt;

                Species::BoidSpecies specie = static_cast<Species::BoidSpecies>(specieInt);
                Boid b(MathsVector<float, 3>{{x, y, z}}, specie);
                b.velocity = MathsVector<float, 3>{{dx, dy, dz}};
                flock.addBoid(b);
            }
        }
    }

    return true;
}

}
