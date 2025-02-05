#include "simpleLife.h"

SimpleLife::SimpleLife(std::string identifier, double avgSpeed, const Vector& startingPosition, double mass, double meetRadius, double TPS)
    : Object(startingPosition), identifier(identifier), mass(mass), meetRadius(meetRadius), TPS(TPS), movementPerTick(avgSpeed / TPS) {
    // Get the average movement per tick
    points.push_back({ 0, startingPosition });
}

double SimpleLife::getMeetRadius() {
    return meetRadius;
}

std::vector<std::tuple<int, Vector>>* SimpleLife::getPoints() {
    return &points;
}
std::vector<Vector>* SimpleLife::getJustPoints() {
    return &justPoints;
}

int SimpleLife::createRandomPath(double width, double length, int tick,int lastTurn) {

    while (true) {
        // Limit degree of motion to create realism
        int randomDeviation = Vector::random(-5, 5);
        // Add or subtract to create new angle and ensure it stays in range
        lastTurn = (lastTurn + randomDeviation) % 360;

        // Get trig values of the angle
        double cosLastTurn = cos((lastTurn + 360) * PI / 180.0);
        double sinLastTurn = sin((lastTurn + 360) * PI / 180.0);

        // Change in x = movement per tick * cos(lastTurn)
        double moveX = movementPerTick * cosLastTurn;

        // Change in y = movement per tick * sin(lastTurn)
        double moveZ = movementPerTick * sinLastTurn;

        // Get new x and y coordinates
        double newX = getPositionOnAxis('x') + moveX;
        double newZ = getPositionOnAxis('z') + moveZ;

        // Check if new coordinates are within the bounds of the space
        if (abs(newX) <= width / 2 && abs(newZ) <= length / 2) {
            moveInDirection('x', moveX);
            moveInDirection('z', moveZ);

            points.push_back({ tick, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
            justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
            
            return lastTurn;
        }
    }
}

void SimpleLife::createTargetPath(double width, double length, int tick, double angle) {

    double cosLastTurn = cos((angle + 360) * PI / 180.0);
    double sinLastTurn = sin((angle + 360) * PI / 180.0);
    double moveX = movementPerTick * cosLastTurn;
    double moveZ = movementPerTick * sinLastTurn;

    double newX = getPositionOnAxis('x') + moveX;
    double newZ = getPositionOnAxis('z') + moveZ;

    moveInDirection('x', moveX);
    moveInDirection('z', moveZ);

    points.push_back({ tick, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
    justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
}

void SimpleLife::resetLifeForm(const Vector& startingPosition) {
    move(startingPosition);
    points.clear();
    justPoints.clear();
    points.push_back({ 0, startingPosition });
}

std::string SimpleLife::getDetails() {
    std::ostringstream oss;
    oss << "ID:" << identifier << ", MPT: " << movementPerTick << ", Points: " << points.size();
    return oss.str();
}
