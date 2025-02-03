#include <iostream>
#include "object.h"
#include "vector.h"

int main() {
    // Create a Vector for the starting position (x = 10, y = 5, z = 3)
    Vector startPos(10, 5, 3);

    // Create an Object at the starting position
    Object obj(startPos);

    // Output the object's initial position
    std::cout << "Initial Position: "
        << "x = " << obj.getPositionOnAxis('x') << ", "
        << "y = " << obj.getPositionOnAxis('y') << ", "
        << "z = " << obj.getPositionOnAxis('z') << std::endl;

    // Move the object to a new position (x = 20, y = 10, z = 6)
    Vector newPos(20, 10, 6);
    obj.move(newPos);

    // Output the object's new position
    std::cout << "New Position: "
        << "x = " << obj.getPositionOnAxis('x') << ", "
        << "y = " << obj.getPositionOnAxis('y') << ", "
        << "z = " << obj.getPositionOnAxis('z') << std::endl;

    // Move the object in the 'x' direction by +5
    obj.moveInDirection('x', 5);

    // Output the object's updated position
    std::cout << "After Moving in X: "
        << "x = " << obj.getPositionOnAxis('x') << ", "
        << "y = " << obj.getPositionOnAxis('y') << ", "
        << "z = " << obj.getPositionOnAxis('z') << std::endl;

    return 0;
}
