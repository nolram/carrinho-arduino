/**
 * @file led.h
 * @brief Header do driver motor.
 * @author Miguel Grinberg
 */
namespace NolramCar
{
    class MotorDriver
    {
    public:
        /**
         * @brief Change the speed of the motor.
         * @param speed The new speed of the motor.
         *  Valid values are between -255 and 255. 
         *  Use positive values to run the motor forward, 
         *  negative values to run it backward and zero to stop the motor.
         */
        virtual void setStatus(int speed) = 0;
        
        /**
         * @brief Retorna o status da lâmpada
         * @return um valor booleano que indica o status da lâmpada, true.
         */
        virtual bool getStatus() const = 0;            
    };
};