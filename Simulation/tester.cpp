#include <iostream>
#include "timer.h"

int main() {
    Timer timer;
    timer.start();

    // Some code you want to time
    for (volatile int i = 0; i < 1e9; ++i);  // Just an example

    std::cout << "Elapsed time: " << timer.elapsed() << " seconds." << std::endl;

    return 0;
}
