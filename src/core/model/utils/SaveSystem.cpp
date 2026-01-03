#include "../../../include/model/utils/SaveSystem.hpp"
#include <fstream>
#include <sstream>

namespace bd {

bool SaveSystem::save(const Simulation& simulation, const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open())
        return false;

    const World& world = simulation.getWorld();
    const Flock& flock = simulation.getFlock();
    const auto& boids = flock.getBoids();

    out << "BOIDS_SAVE_V1\n\n";

    // --- World ---
    out << "WORLD\n";
    out << "width " << world.getWidth() << "\n";
    out << "height " << world.getHeight() << "\n\n";

    // --- Boids ---
    out << "BOIDS\n";
    out << "count " << boids.getsize() << "\n";

    for (size_t i = 0; i < boids.getsize(); ++i) {
        const Boid& b = boids[i];

        Vec2<float> dir = b.velocity.normalized();
        if (dir.length() < 0.0001f)
            dir = Vec2<float>(1.0f, 0.0f);

        out << "boid "
            << b.position.x << " "
            << b.position.y << " "
            << dir.x << " "
            << dir.y << "\n";
    }

    return true;
}

bool SaveSystem::load(Simulation& simulation, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        return false;

    std::string line;

    std::getline(in, line);
    if (line != "BOIDS_SAVE_V1")
        return false;

    World& world = simulation.getWorld();
    Flock& flock = simulation.getFlock();

    flock.getBoids().clear();

    while (std::getline(in, line)) {
        if (line == "WORLD") {
            std::getline(in, line);
            world = World(std::stof(line.substr(6)), world.getHeight());

            std::getline(in, line);
            world = World(world.getWidth(), std::stof(line.substr(7)));
        }
        else if (line == "BOIDS") {
            std::getline(in, line);
            int count = std::stoi(line.substr(6));

            for (int i = 0; i < count; ++i) {
                std::getline(in, line);
                std::istringstream iss(line);

                std::string tag;
                float x, y, dx, dy;

                iss >> tag >> x >> y >> dx >> dy;

                Boid b(x, y);
                b.velocity = Vec2<float>(dx, dy);
                flock.addBoid(b);
            }
        }
    }

    return true;
}

}
