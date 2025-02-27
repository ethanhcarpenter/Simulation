#pragma once

#include "vector.h"

class Object {
private:
    Vector position;//object's position

public:
    //constructor to initialize position
    Object(const Vector& startingPosition);

    //relocate the object to a new position
    void move(const Vector& newPosition);

    //move along a specified axis
    void moveInDirection(char axis, double amount);

    //get the position vector
    const Vector& getPosition() const;

    //get the position value on a specified axis
    double getPositionOnAxis(char axis) const;
};

