#pragma once

#include "TimeService.h"

#include <optional>
#include <iostream>
#include <map>

enum class SensorID {
    RANDOM_INT_SENSOR_1,
    RANDOM_INT_SENSOR_2,
    STRING_SENSOR_1,
};

std::map<SensorID, std::string> SENSOR_ID_STRING = {
    {SensorID::RANDOM_INT_SENSOR_1, "RANDOM_INT_SENSOR_1"},
    {SensorID::RANDOM_INT_SENSOR_2, "RANDOM_INT_SENSOR_2"},
    {SensorID::STRING_SENSOR_1, "STRING_SENSOR_1"},
};

class SensorBase {

protected:
    SensorID id;

public:

    SensorBase(SensorID id) : id(id) {}

    // Update the sensor and return the sensor-specific data
    virtual void* update() = 0;

    // Get the size of the sensor-specific data, in bytes
    virtual size_t sensorDataBytes() const = 0;

    SensorID getID() const {
        return id;
    }

    virtual ~SensorBase() = default;
};

template <typename T>
class Sensor : public SensorBase {
private:

    // Call getData() every pollPeriod updates
    int pollPeriod;

    // The current phase of the polling period
    int counter;

    // The time of the last update
    long lastUpdateTime;

protected:
    // Return the sensor-specific data
    virtual T getData() = 0; 

    // The last polled value
    T storedValue;

    // The time service
    TimeService* time;

public:
    Sensor(SensorID id, TimeService* timeService, int pollPeriod)
        : SensorBase(id), pollPeriod(pollPeriod), counter(pollPeriod), storedValue{}, time(timeService) {}

    // Call getData() every pollPeriod updates, and return the new value when updated
    // Otherwise, return nothing
    void* update() override {
        counter++;

        // Check if we've reached the polling period
        if (counter >= pollPeriod) {
            storedValue = getData();
            lastUpdateTime = time->millis();
            counter = 0;
            return &storedValue;
        }

        // Return nothing if not updated
        return nullptr;
    }

    // Poll function returning the stored value and the time of the last update
    std::pair<T, long> poll() const {
        return {storedValue, lastUpdateTime};
    }

    virtual ~Sensor() = default;
};