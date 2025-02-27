#include "confinement.h"

//constructor
Confinement::Confinement(double length, double width, std::string metric, int TPS)
    : length(length), width(width), metric(metric), TPS(TPS) {
}

//return ticks per second
int Confinement::getTPS() {
    return TPS;
}

//return length of confinement
double Confinement::getLength() {
    return length;
}

//return width of confinement
double Confinement::getWidth() {
    return width;
}

//create a simple life form within the confinement
void Confinement::addSimpleLife(std::string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius) {
    lifeForms[identifier] = std::make_unique<SimpleLife>(identifier, avgSpeed, startingPosition, mass, meetRadius, getTPS());
}

//return a life form with specified identifier
SimpleLife* Confinement::getLifeForm(std::string identifier) {
    return lifeForms[identifier].get();
}

//create a random vector within the Confinement
Vector Confinement::createRandomVector(bool debug) {
	return Vector::randomise(-length / 2, -width / 2, length / 2, width / 2, debug);
}

//return all life forms
std::vector<SimpleLife*> Confinement::getAllLifeForms() {
    std::vector<SimpleLife*> allLife;
    for (auto it = lifeForms.begin(); it != lifeForms.end(); ++it) {
        allLife.push_back(it->second.get());
    }
    return allLife;
}

//clear the list of life forms
void Confinement::removeAllLife() {
    lifeForms.clear();
}
