#pragma once

#include "TimeService.h"
#include <chrono>

class ComputerTimeService : public TimeService {

private:
    std::__1::chrono::steady_clock::time_point start;

public:
    ComputerTimeService();
    long millis() const override; // Override the pure virtual function
};