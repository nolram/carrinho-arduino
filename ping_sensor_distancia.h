/**
 * @file newping_distance_sensor.h
 * @brief distance sensor driver for distance sensors supported by the NewPing library.
 * @author Miguel Grinberg
 */

#include "sensor_distancia.h"

namespace NolramCar
{
    class DistanceSensor : public SensorDeDistancia
    {
    public:
        DistanceSensor(int triggerPin, int echoPin, int maxDistance)
            : SensorDeDistancia(maxDistance), 
              sensor(triggerPin, echoPin, maxDistance)
        {
        }
        
        virtual unsigned int getDistancia()
        {
            int distance = sensor.ping_cm();
            if (distance <= 0)
                return maxDistancia;
            return distance;
        }
    private:
        NewPing sensor;
    };
};
