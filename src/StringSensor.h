#pragma once

#include "Sensor.h"
#include <iostream>

// SensorData struct to hold a single integer
struct StringSensorData {
    const char* str;
};

// TestSensor class that inherits from Sensor
class RandomStringSensor : public Sensor<StringSensorData> {


protected:

    // Generate a random integer between 0 and 99 as the test sensor data
    StringSensorData getData() override {

        StringSensorData data;
        data.str = "Hello World!";

        return data;
    }

public:

    RandomStringSensor(SensorID id, TimeService* timeService, int pollPeriod)
        : Sensor<StringSensorData>(id, timeService, pollPeriod) {}

    size_t sensorDataBytes() const override {
        return strlen(storedValue.str);
    }
};