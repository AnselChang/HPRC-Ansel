#pragma once

#include "Sensor.h"
#include <iostream>

// SensorData struct to hold a single integer
struct IntSensorData {
    int value;
};

// TestSensor class that inherits from Sensor
class RandomIntSensor : public Sensor<IntSensorData> {


protected:

    // Generate a random integer between 0 and 99 as the test sensor data
    IntSensorData getData() override {

        IntSensorData data;
        data.value = rand() % 100;
        return data;
    }

public:

    RandomIntSensor(SensorID id, TimeService* timeService, int pollPeriod)
        : Sensor<IntSensorData>(id, timeService, pollPeriod) {}

    size_t sensorDataBytes() const override {
        return sizeof(IntSensorData);
    }
};