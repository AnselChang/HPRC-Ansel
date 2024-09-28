#pragma once

#include "Sensor.h"

#include <map>
#include <memory>

class SensorManager {
private:
    std::map<SensorID, std::unique_ptr<SensorBase>> sensors;

public:
    // Add a sensor to the manager
    void addSensor(std::unique_ptr<SensorBase> sensor) {
        sensors[sensor->getID()] = std::move(sensor);
    }

    // Get a sensor by its ID
    SensorBase* getSensor(SensorID id) {
        auto it = sensors.find(id);
        if (it != sensors.end()) {
            return it->second.get();
        }
        return nullptr;  // Return nullptr if not found
    }

    // Templated function to poll a specific type of sensor
    template<typename T>
    std::pair<T, long> pollSensor(SensorID id) {

        // Get the sensor by ID
        SensorBase* sensor = getSensor(id);
        if (!sensor) {
            throw std::runtime_error("Sensor not found.");
        }

        // Attempt to cast to the specific type of sensor
        Sensor<T>* specificSensor = dynamic_cast<Sensor<T>*>(sensor);
        if (!specificSensor) {
            throw std::runtime_error("Requested sensor id " + SENSOR_ID_STRING[id] + " is not of type " + typeid(T).name());
        }

        // Poll the sensor
        return specificSensor->poll();
    }

    // Update all sensors
    void updateAll() {
        for (auto& pair : sensors) {

            void* sensorData = pair.second->update();

            // TEMP ONLY, REPLACE WITH TELEMETRY: If sensor polled new data, print the raw bytes
            if (sensorData) {
                size_t bytes = pair.second->sensorDataBytes();

                std::cout << "Raw data from " << SENSOR_ID_STRING[pair.second->getID()] << " with length " << bytes << ": ";
                for (size_t i = 0; i < bytes; i++) {
                    std::cout << static_cast<int>(reinterpret_cast<unsigned char*>(sensorData)[i]) << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    // Print information about all sensors
    void printAllSensors() const {
        for (const auto& pair : sensors) {
            std::cout << "Sensor ID: " << static_cast<int>(pair.first) << std::endl;
        }
    }
};