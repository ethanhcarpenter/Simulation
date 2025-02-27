#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "simpleLife.h"
#include "vector.h"

class Confinement {
private:
    std::map<std::string, std::unique_ptr<class SimpleLife>> lifeForms;  //store life forms
    const double length;//length of the confinement
    const double width;//width of the confinement
    const std::string metric;//metric system used
    const int TPS;//ticks per second

public:
    //constructor
    Confinement(double length, double width, std::string metric, int TPS);

    //return ticks per second
    int getTPS();

    //return the length of the confinement
    double getLength();

    //return the width of the confinement
    double getWidth();

    //add a new simple life form
    void addSimpleLife(std::string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius);

    //return a specific life form by its identifier
    SimpleLife* getLifeForm(std::string identifier);

    //return all life forms
    std::vector<SimpleLife*> getAllLifeForms();

    //create random Vector within Confinement
	Vector createRandomVector(bool debug=false);

    //remove all life forms
    void removeAllLife();
};
