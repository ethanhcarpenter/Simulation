#include "object.h"

// Initialize with starting position
Object::Object(const Vector& startingPosition)
    : position(startingPosition) {
}

// Move object to new position
void Object::move(const Vector& newPosition) {
    position = newPosition;
}

// Move in specified direction (axis and amount)
void Object::moveInDirection(char axis, double amount) {
    position.moveValueOnAxis(axis, amount);
}

// Return position vector
const Vector& Object::getPosition() const {
    return position;
}

// Return position value on specified axis
double Object::getPositionOnAxis(char axis) const {
    return position.getValueOnAxis(axis);
}
