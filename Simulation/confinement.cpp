#include "confinement.h"

// Constructor
Confinement::Confinement(double length, double width, std::string metric, int TPS)
    : length(length), width(width), metric(metric), TPS(TPS) {
}

// Return ticks per second
int Confinement::getTPS() {
    return TPS;
}

// Return length of confinement
double Confinement::getLength() {
    return length;
}

// Return width of confinement
double Confinement::getWidth() {
    return width;
}

// Create a simple life form within the confinement
void Confinement::addSimpleLife(std::string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius) {
    lifeForms[identifier] = std::make_unique<SimpleLife>(identifier, avgSpeed, startingPosition, mass, meetRadius, getTPS());
}

// Return a life form with specified identifier
SimpleLife* Confinement::getLifeForm(std::string identifier) {
    return lifeForms[identifier].get();
}

// Create a random vector within the Confinement
Vector Confinement::createRandomVector(bool debug) {
	return Vector::randomise(-length / 2, -width / 2, length / 2, width / 2, debug);
}

// Return all life forms
std::vector<SimpleLife*> Confinement::getAllLifeForms() {
    std::vector<SimpleLife*> allLife;
    for (auto it = lifeForms.begin(); it != lifeForms.end(); ++it) {
        allLife.push_back(it->second.get());
    }
    return allLife;
}

// Clear the list of life forms
void Confinement::removeAllLife() {
    lifeForms.clear();
}
