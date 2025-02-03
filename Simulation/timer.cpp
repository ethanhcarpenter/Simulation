#include "timer.h"

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() {
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(endTime - startTime).count();
}
