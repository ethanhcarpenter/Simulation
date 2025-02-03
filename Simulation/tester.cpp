#include <iostream>
#include "simpleLife.h"
#include "vector.h"
#include "confinement.h"

int main() {
    // Create a confinement (length = 100, width = 100, metric = "meters", TPS = 30)
    Confinement confinement(100.0, 100.0, "meters", 30);

    // Create a life form and add it to the confinement
    Vector startPos(10.0, INF, 0.0);
    confinement.addSimpleLife("Life1", 5.0, startPos, 70.0, 2.0);

    // Retrieve and display the life form
    SimpleLife* lifeForm = confinement.getLifeForm("Life1");
    std::cout << "Life form 'Life1' position: "
        << "x = " << lifeForm->getPositionOnAxis('x') << ", "
        << "y = " << lifeForm->getPositionOnAxis('y') << ", "
        << "z = " << lifeForm->getPositionOnAxis('z') << std::endl;

    // Create a random path
    lifeForm->createRandomPath(10.0, 100.0, 100.0);

    lifeForm->resetLifeForm(startPos);

    // Create a path to a target
    Vector target(50.0, INF, 0.0);
    lifeForm->createTargetPath(10.0, 100.0, 100.0, target);

    return 0;
}
