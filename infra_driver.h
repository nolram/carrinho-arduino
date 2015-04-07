/**
 * @file infravermelho.h
 * @brief Header do sensor de distância do infravermelho
 * @author Marlon Baptista de Quadros
 */
namespace NolramCar
{
    class InfraDriver
    {
    public:

        virtual void setStatus() = 0;

        /**
         * @brief Retorna um valor booleano indicando se o objeto está próximo do sensor
         * @return um valor boolean.
         */
        virtual bool getStatus() const = false;
    };
};