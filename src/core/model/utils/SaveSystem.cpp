#include "../../../include/model/utils/SaveSystem.hpp"
#include <fstream>
#include <sstream>

namespace bd {

bool SaveSystem::save(const Simulation& simulation, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open())
        return false;
        
    const Flock& flock = simulation.getFlock();
    const auto& boids = flock.getBoids();

    out << "BOIDS_SAVE_V2\n\n";

    // --- World ---
    out << "WORLD\n";
    out << "width "  << settings::worldWidth  << "\n";
    out << "height " << settings::worldHeight << "\n";
    out << "depth "  << settings::worldDeepth  << "\n\n";

    // --- Boids ---
    out << "BOIDS\n";
    out << "count " << boids.getsize() << "\n";

    for (size_t i = 0; i < boids.getsize() ; ++i) {
        const Boid& b = boids[i];

        Vec3<float> dir = b.velocity.normalized();
        if (dir.lengthSq() < 1e-6f) {
            dir = Vec3<float>(1.f, 0.f, 0.f);
        }

        out << "boid " << b.position.x << " " << b.position.y << " " << b.position.z << " " << dir.x << " " << dir.y << " " << dir.z << "\n";
    }

    return true;
}

bool SaveSystem::load(Simulation& simulation, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        return false;

    std::string line;
    std::getline(in, line);

    if (line != "BOIDS_SAVE_V2")
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

            world = World(width, height, deepth);
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

                iss >> tag >> x >> y >> z >> dx >> dy >> dz;

                Boid b(x, y, z);
                b.velocity = Vec3<float>(dx, dy, dz);
                flock.addBoid(b);
            }
        }
    }

    return true;
}

}
