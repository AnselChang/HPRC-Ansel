#include "RandomIntSensor.h"
#include "StringSensor.h"
#include "SensorManager.h"
#include "ComputerTimeService.h"

#include <iostream>

int main() {
    
    ComputerTimeService time;
    SensorManager sensors;

    sensors.addSensor(std::make_unique<RandomIntSensor>(SensorID::RANDOM_INT_SENSOR_1, &time, 5));
    sensors.addSensor(std::make_unique<RandomIntSensor>(SensorID::RANDOM_INT_SENSOR_2, &time, 2));
    sensors.addSensor(std::make_unique<RandomStringSensor>(SensorID::STRING_SENSOR_1, &time, 1));

    for (int i = 0; i < 20; i++) {
        
        sensors.updateAll();

        auto [value, time] = sensors.pollSensor<IntSensorData>(SensorID::RANDOM_INT_SENSOR_1);
        std::cout << "Value: " << value.value << " at time: " << time << std::endl;

        auto [value2, time2] = sensors.pollSensor<IntSensorData>(SensorID::RANDOM_INT_SENSOR_2);
        std::cout << "Value: " << value2.value << " at time: " << time2 << std::endl;

        auto [value3, time3] = sensors.pollSensor<StringSensorData>(SensorID::STRING_SENSOR_1);
        std::cout << "Value: " << value3.str << " at time: " << time3 << std::endl;

    }


    return 0;
}
