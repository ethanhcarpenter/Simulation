#include "simpleLife.h"

SimpleLife::SimpleLife(std::string identifier, double avgSpeed, Vector startingPosition, double mass, double meetRadius, double TPS)
    : Object(startingPosition), identifier(identifier), mass(mass), meetRadius(meetRadius), TPS(TPS), movementPerTick(avgSpeed / TPS) {
    // Get the average movement per tick
    points.push_back({ 0, startingPosition });
}

double SimpleLife::getMeetRadius() {
    return meetRadius;
}

std::vector<std::tuple<int, Vector>>* SimpleLife::getPath() {
    return &points;
}

void SimpleLife::createRandomPath(double time, double width, double length) {
    points.reserve(time * TPS + 10);

    // Initial turn from the center
    int lastTurn = Vector::random(-360, 360);

    // Move every tick
    for (int i = 0; i < int(TPS * time); i++) {
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

                points.push_back({ i, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
                justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
                break;
            }
        }
    }

    // Create file of points
    std::string filename = "./outputs/paths/generatedPaths/random_" + identifier + ".txt";
    std::string pointsStr = "";
    for (auto& point : justPoints) {
        pointsStr += point.stringFileRepresentation() + "\n";
    }
    FileHandler::writeToFile(filename, pointsStr);
}

void SimpleLife::createTargetPath(double time, double width, double length, Vector target) {
    points.reserve(time * TPS + 10);

    double dx = target.getValueOnAxis('x') - getPositionOnAxis('x');
    double dz = target.getValueOnAxis('z') - getPositionOnAxis('z');
    double angle;

    if (dx < 0 && dz < 0) {
        angle = atan(dx / dz) * 180 / PI;
        angle = 270 - abs(angle);
    }
    else if (dx > 0 && dz < 0) {
        angle = atan(dx / dz) * 180 / PI;
        angle = 270 + abs(angle);
    }
    else if (dx < 0 && dz > 0) {
        angle = atan(dx / dz) * 180 / PI;
        angle = 90 + abs(angle);
    }
    else if (dx > 0 && dz > 0) {
        angle = atan(dx / dz) * 180 / PI;
        angle = (90 - abs(angle));
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

    std::string filename = "./outputs/debug/angles/angle_" + identifier + ".txt";
    std::ostringstream oss;
    oss << "target: " << target.stringDebugRepresentation() << "\n"
        << "Current Position: " << getPosition().stringDebugRepresentation() << "\n"
        << "Difference : " << "dx: " << dx << " dz: " << dz << "\n"
        << "Angle: " << angle << "\n";
    FileHandler::writeToFile(filename, oss.str());

    // Move every tick
    for (int i = 0; i < int(TPS * time); i++) {
        if (round(getPositionOnAxis('x') * 3) / 3 == round(target.getValueOnAxis('x') * 3) / 3 &&
            round(getPositionOnAxis('z') * 3) / 3 == round(target.getValueOnAxis('z') * 3) / 3) {
            break;
        }

        double cosLastTurn = cos((angle + 360) * PI / 180.0);
        double sinLastTurn = sin((angle + 360) * PI / 180.0);
        double moveX = movementPerTick * cosLastTurn;
        double moveZ = movementPerTick * sinLastTurn;

        double newX = getPositionOnAxis('x') + moveX;
        double newZ = getPositionOnAxis('z') + moveZ;

        moveInDirection('x', moveX);
        moveInDirection('z', moveZ);

        points.push_back({ i, Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') } });
        justPoints.push_back(Vector{ getPositionOnAxis('x'), getPositionOnAxis('y'), getPositionOnAxis('z') });
    }

    filename = "./outputs/paths/generatedPaths/target_" + identifier + ".txt";
    std::string pointsStr = "";
    for (auto& point : justPoints) {
        pointsStr += point.stringFileRepresentation() + "\n";
    }
    FileHandler::writeToFile(filename, pointsStr);
}

void SimpleLife::resetLifeForm(Vector startingPosition) {
    move(startingPosition);
    points.clear();
    points.push_back({ 0, startingPosition });
}

std::string SimpleLife::getDetails() {
    std::ostringstream oss;
    oss << "ID:" << identifier << ", MPT: " << movementPerTick << ", Points: " << points.size();
    return oss.str();
}
