/**
 * @file infravermelho.h
 * @brief Header do sensor de distância do infravermelho
 * @author Marlon Baptista de Quadros
 */
#include "infra_driver.h"
namespace NolramCar
{
    class SensorInfravermelho : InfraDriver
    {
    public:
        SensorInfravermelho(int numberPort): currentStatus(1), pinMode (numberPort, INPUT)
        {

        }

        void setStatus(){
            currentStatus = digitalRead(9);
        }

        bool getStatus(){
            if(currentStatus == 0){
                return true;
            }else{
                return false;
            }
        }


    private:
        int currentStatus;

    };
};