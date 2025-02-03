#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "simpleLife.h"
#include "vector.h"

class Confinement {
private:
    std::map<std::string, std::unique_ptr<class SimpleLife>> lifeForms;  // Store life forms
    const double length;  // Length of the confinement
    const double width;   // Width of the confinement
    const std::string metric;  // Metric system used
    const int TPS;  // Ticks per second

public:
    // Constructor
    Confinement(double length, double width, std::string metric, int TPS);

    // Return ticks per second
    int getTPS();

    // Return the length of the confinement
    double getLength();

    // Return the width of the confinement
    double getWidth();

    // Add a new simple life form
    void addSimpleLife(std::string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius);

    // Return a specific life form by its identifier
    SimpleLife* getLifeForm(std::string identifier);

    // Return all life forms
    std::vector<SimpleLife*> getAllLifeForms();

    // Remove all life forms
    void removeAllLife();
};
