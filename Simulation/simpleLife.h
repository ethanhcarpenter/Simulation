#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "object.h"
#include "vector.h"
#include "fileHandler.h"
#include <cmath>
#include <sstream>

class SimpleLife : public Object {
private:
    const double movementPerTick;
    const double mass;
    const double meetRadius;
    const double TPS;
    const std::string identifier;
    std::vector<std::tuple<int, Vector>> points;
    std::vector<Vector> justPoints;

public:
    // Constructor
    SimpleLife(std::string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius, double TPS);

    // Return meet radius
    double getMeetRadius();

    // Return the generated path
    std::vector<std::tuple<int, Vector>>* getPath();

    // Randomly generate a walk
    void createRandomPath(double time, double width, double length);

    // Create a path to a target
    void createTargetPath(double time, double width, double length, Vector target);

    // Reset all values and return to a specified position
    void resetLifeForm(Vector startingPosition);

    // Debug: Returns a string of the movement per tick and amount of points in the path
    std::string getDetails();
};
