#include "simulation.h"


Simulation::Simulation(int TPS) : TPS(TPS), confinement(nullptr) {}

void Simulation::createConfinement(double length, double width, std::string metric) {
    confinement = std::make_unique<Confinement>(length, width, metric, TPS);
}

Confinement& Simulation::getConfinement() {
    return *confinement;
}

void Simulation::generateRandomPath(std::string identifier, double time) {
    SimpleLife* life = confinement->getLifeForm(identifier);
    Vector start = life->getPosition();
    int lastTurn = Vector::random(-360, 360);

    for (int tick = 0; tick < time * TPS; tick++) {
        lastTurn = life->createRandomPath(confinement->getWidth(), confinement->getLength(), tick, lastTurn);
    }

    std::string filename = "random\\"+identifier + ".txt";
    std::string points;
    for (auto point : *life->getJustPoints()) {
        points += point.stringFileRepresentation() + "\n";
    }
    FileHandler::writeToFile(filename, points);
    life->resetLifeForm(start);
}

void Simulation::generateTargetPath(std::string identifier, double time, Vector target) {
    SimpleLife* life = confinement->getLifeForm(identifier);
	Vector start = life->getPosition();
    double angle = calculateAngle(life->getPosition(), target);

    for (int tick = 0; tick < time * TPS; tick++) {
        if (checkIfReached(life->getPosition(), target)) {
            break;
        }
        life->createTargetPath(confinement->getWidth(), confinement->getLength(), tick, angle);
    }
    std::string filename = "target/" + identifier + ".txt";
    std::string points;
    for (auto point : *life->getJustPoints()) {
        points += point.stringFileRepresentation() + "\n";
    }
    FileHandler::writeToFile(filename, points);
	life->resetLifeForm(start);
}

double Simulation::calculateAngle(Vector current, Vector target) {
    double dx = target.getValueOnAxis('x') - current.getValueOnAxis('x');
    double dz = target.getValueOnAxis('z') - current.getValueOnAxis('z');
    double angle;

    if (dx < 0 && dz < 0) {
        angle = atan(dx / dz) * 180 / PI;
        angle = 270 - std::abs(angle);
    }
    else if (dx > 0 && dz < 0) {
        angle = atan(dx / dz) * 180 / PI;
        angle = 270 + std::abs(angle);
    }
    else if (dx < 0 && dz > 0) {
        angle = atan(dx / dz) * 180 / PI;
        angle = 90 + std::abs(angle);
    }
    else if (dx > 0 && dz > 0) {
        angle = (90 - std::abs(atan(dx / dz) * 180 / PI));
    }
    else if (dz == 0 && dx > 0) {
        angle = 0;
    }
    else if (dz == 0 && dx < 0) {
        angle = 180;
    }
    else if (dx == 0 && dz > 0) {
        angle = 90;
    }
    else if (dx == 0 && dz < 0) {
        angle = 270;
    }

    return angle;
}

bool Simulation::checkIfReached(Vector current, Vector target) {
    return (std::round(current.getValueOnAxis('x') * 3) / 3 == std::round(target.getValueOnAxis('x') * 3) / 3 &&
        std::round(current.getValueOnAxis('z') * 3) / 3 == std::round(target.getValueOnAxis('z') * 3) / 3);
}
