#pragma once

#include <memory>
#include <string>
#include <cmath>
#include <iostream>
#include "confinement.h"
#include "fileHandler.h"
#include "vector.h"

class Simulation {
private:
    std::unique_ptr<Confinement> confinement;
    const int TPS;

public:
    Simulation(int TPS);

    void createConfinement(double length, double width, std::string metric);
    Confinement& getConfinement();

    void generateRandomPath(std::string identifier, double time);
    void generateTargetPath(std::string identifier, double time, Vector target);

    double calculateAngle(Vector current, Vector target);
    bool checkIfReached(Vector current, Vector target);
};
