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
    SimpleLife(std::string identifier, double avgSpeed, const Vector& startingPosition, double mass, double meetRadius, double TPS);

    // Return meet radius
    double getMeetRadius();

    // Return the generated path
    std::vector<std::tuple<int, Vector>>* getPoints();

    std::vector<Vector>* getJustPoints();

    // Randomly generate a walk
    int createRandomPath( double width, double length, int tick , int lastTurn);

    // Create a path to a target
    void createTargetPath(double width, double length, int tick,double angle);

    // Reset all values and return to a specified position
    void resetLifeForm(const Vector& startingPosition);

    // Debug: Returns a string of the movement per tick and amount of points in the path
    std::string getDetails();
};
