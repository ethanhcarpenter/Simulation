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
    //constructor
    Simulation(int TPS);
    //create the confinement
    void createConfinement(double length, double width, std::string metric);
    Confinement& getConfinement();
    //create a list of random points
    void generateRandomPath(std::string identifier, double time);
    //create a list of points that leads to a point
    void generateTargetPath(std::string identifier, double time, Vector target);

    //calculate the angle between 2 points
    double calculateAngle(Vector current, Vector target);
    //check if 2 vectors are the same or close to eachother
    bool checkIfReached(Vector current, Vector target);
};
