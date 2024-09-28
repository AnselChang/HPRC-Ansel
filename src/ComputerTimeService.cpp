#include "ComputerTimeService.h"

ComputerTimeService::ComputerTimeService() : start(std::chrono::steady_clock::now()) {}

long ComputerTimeService::millis() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = now - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}