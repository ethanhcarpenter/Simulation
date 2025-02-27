#include <iostream>
#include <vector>
#include "simulation.h"

int main() {
    FileHandler::clearDirectory("./random");
    FileHandler::clearDirectory("./target");
    // Define number of life forms
    const int numLifeForms = 5;
    const double time = 1000;

    // Create a Simulation instance with a tick rate of 60 TPS
    Simulation sim(60);

    // Create a confinement area (e.g., 1000x1000 meters)
    sim.createConfinement(250, 250, "meters");

    // Generate life forms
    std::vector<std::string> lifeIdentifiers;
    for (int i = 0; i < numLifeForms; i++) {
        std::string id = "life" + std::to_string(i + 1);
        lifeIdentifiers.push_back(id);
        //sim.getConfinement().addSimpleLife(id, 1.0, sim.getConfinement().createRandomVector(), 1.0, 1.0);
        sim.getConfinement().addSimpleLife(id, 1.0, Vector{100,INF,0}, 1.0, 1.0);
    }

    // Run random movement simulation for all life forms
    for (const auto& id : lifeIdentifiers) {
        sim.generateRandomPath(id, time);
        std::cout << "Random path for " << id << " generated and saved." << std::endl;
    }

    // Define a target position
    //Vector target = sim.getConfinement().createRandomVector(true);
    Vector target = Vector{ 0,INF,0 };

    // Run target movement simulation for all life forms
    for (const auto& id : lifeIdentifiers) {
        sim.generateTargetPath(id, time, target);
        std::cout << "Targeted path for " << id << " generated and saved." << std::endl;
    }

    return 0;
}
