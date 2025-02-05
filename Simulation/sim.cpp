#include <iostream>
#include "simulation.h"

int main() {
    // Create a Simulation instance with a tick rate of 60 TPS
    Simulation sim(60);

    // Create a confinement area (e.g., 100x100 meters)
    sim.createConfinement(1000.0, 1000.0, "meters");

    // Make a life
	sim.getConfinement().addSimpleLife("life1", 1.0, Vector(0.0, 0.0, 0.0), 1.0, 1.0);

    // Generate a random movement path for a life form with identifier "life1" over 10 seconds
    sim.generateRandomPath("life1", 10.0);
    std::cout << "Random path for life1 generated and saved." << std::endl;

    // Define a target position
    Vector target(50.0, 0.0, 50.0);

    // Generate a target movement path for "life1" over 10 seconds towards the target position
    sim.generateTargetPath("life1", 10.0, target);
    std::cout << "Targeted path for life1 generated and saved." << std::endl;

    return 0;
}
