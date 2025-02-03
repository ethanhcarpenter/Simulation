#pragma once

#include "vector.h"

class Object {
private:
    Vector position;  // Object's position

public:
    // Constructor to initialize position
    Object(const Vector& startingPosition);

    // Relocate the object to a new position
    void move(const Vector& newPosition);

    // Move along a specified axis
    void moveInDirection(char axis, double amount);

    // Get the position vector
    const Vector& getPosition() const;

    // Get the position value on a specified axis
    double getPositionOnAxis(char axis) const;
};

