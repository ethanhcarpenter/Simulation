#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;

public:
    void start();  // Starts the timer
    double elapsed();  // Returns the elapsed time in seconds
};
