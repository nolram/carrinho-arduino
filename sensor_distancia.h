/**
 * @file sensor_distancia.h
 * @brief Header do sensor distancia.
 * @author Marlon Baptista de Quadros
 */
namespace NolramCar
{
    class SensorDeDistancia
    {
    public:
        /**
          * @brief Class constructor.
          * @param distance The maximum distance in centimeters that needs to be tracked.
          */
        SensorDeDistancia(unsigned int distancia) : maxDistancia(distancia) {}
        
        /**
         * @brief Return the distance to the nearest obstacle in centimeters.
         * @return the distance to the closest object in centimeters 
         *   or maxDistance if no object was detected
         */
        virtual unsigned int getDistancia() = 0;
        
    protected:
        unsigned int maxDistancia;
    };
};