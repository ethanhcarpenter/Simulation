#pragma once
#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;

public:
    //starts the timer
    void start();
    //returns the elapsed time in seconds
    double elapsed();
};
