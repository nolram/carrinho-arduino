/**
 * @file code_car.ino
 * @brief Robo Arduino.
 * @author Marlon Baptista de Quadros
 */
#define LOGGING

#define ENABLE_ADAFRUIT_MOTOR_DRIVER
#define ENABLE_NEWPING_DISTANCE_SENSOR_DRIVER
// constants
#// constants
#define RUN_TIME 30                     /**< seconds the robot will run */
#define TOO_CLOSE 3                    /**< distance to obstacle in centimeters */
#define MAX_DISTANCE (TOO_CLOSE * 20)   /**< maximum distance to track with sensor */
#define RANDOM_ANALOG_PIN 5             /**< unused analog pin to use as random seed */

#ifdef ENABLE_ADAFRUIT_MOTOR_DRIVER
#include <AFMotor.h>
#include "motor.h"
#define LEFT_MOTOR_INIT 1
#define RIGHT_MOTOR_INIT 3
#endif

#define VELOCIDADE_L 150
#define VELOCIDADE_R 150

#ifdef ENABLE_NEWPING_DISTANCE_SENSOR_DRIVER
#include <NewPing.h>
#include "ping_sensor_distancia.h"
#define DISTANCE_SENSOR_INIT 14,15,MAX_DISTANCE
#endif

//#define BUTTON_CODE 10
//#define BUZZER 2
//#define SENSOR_INFRAVERMELHO 9

#include "log.h"
#include "movimento.h"

namespace NolramCar
{
  class Robo
  {
public:
    /*
         * @brief Class constructor.
     */
    Robo()
: 
      leftMotor(LEFT_MOTOR_INIT), rightMotor(RIGHT_MOTOR_INIT),
      distanceSensor(DISTANCE_SENSOR_INIT), distanceAverage(TOO_CLOSE * 10)
      {
        initialize();
      }

    /*
         * @brief Initialize the robot state.
     */
    void initialize()
    {
      Serial.begin (9600);
      randomSeed(analogRead(RANDOM_ANALOG_PIN));
      endTime = millis() + RUN_TIME * 1000;
      //pinMode(BUZZER, OUTPUT);
      //pinMode(BUTTON_CODE, INPUT); //Pino com botão será entrada
      #ifdef SENSOR_INFRAVERMELHO
      pinMode (SENSOR_INFRAVERMELHO, INPUT);
      #endif
      //moveForward();
      //movingForward();
      //moveBackward();
    }

    /*
         * @brief Update the state of the robot based on input from sensor and remote control.
     *  Must be called repeatedly while the robot is in operation.
     */
    void run()
    {      
      //moveBackward();
      //turnLeft();
      //turnRight();
      unsigned long currentTime = millis();
      int distance = distanceAverage.add(distanceSensor.getDistancia());     
         if (obstacleAhead(distance)){
           log("state: %d, currentTime: %lu, distance: %u", 
                state, currentTime, distance); 
           if(!turning()){
             turn(currentTime);
           }
         }
         else if (turning()) {
           if (doneTurning(currentTime, distance))
           moveForward();
         }
         
      /*
      //moveBackward();
     unsigned long currentTime = millis();
      //int distance = distanceAverage.add(distanceSensor.getDistancia());
      //log("state: %d, currentTime: %lu, distance: %u", 
      //          state, currentTime, distance);      
         if (sensorBackward()){
           //log("1");
           
           if(!turning()){
             turn(currentTime);
             //log("2");
           }
         }
         else if (turning()) {
           //log("3");
           if (doneTurning(currentTime))
             //log("4");
             moveBackward();
         }
      
      */

      /*
      if(movingForward()){
        if (obstacleAhead(distance)){
          log("1");
          moveBackward();
        }
        else{
          log("2");
          moveForward();
        }
      }
      else if(movingBackward()){
        if (sensorBackward()){
          log("3");
          moveForward();
        }
        else{
          log("4");
          moveBackward();
        }
      }
      else if((sensorBackward()) && (obstacleAhead(distance))){
        log("5");
        turn(currentTime);
      }
      else if (turning()) {
        log("6");
        if (doneTurning(currentTime, distance))
          moveBackward();
          log("7");
      }
*/

      /*if (stopped())
       return;
       unsigned long currentTime = millis();
       int distance = distanceAverage.add(distanceSensor.getDistancia());
       Serial.println(distance);
       //log("state: %d, currentTime: %lu, distance: %u\n", state, currentTime, distance);
       
       //btnParar();
       if (doneRunning(currentTime))
       stop();
       else if (moving()) {
       if (obstacleAhead(distance))
       turn(currentTime);
       }
       else if (turning()) {
       if (doneTurning(currentTime, distance))
       move();
       }*/
    }

protected:
    void moveBackward()
    {
      leftMotor.setSpeed(VELOCIDADE_L);
      rightMotor.setSpeed(-VELOCIDADE_R);
      state = stateMovingBackward;
    }

    void moveForward()
    {
      leftMotor.setSpeed(-VELOCIDADE_L);
      rightMotor.setSpeed(VELOCIDADE_R);
      state = stateMovingForward;
    }
    
    void turnLeft(){
      leftMotor.setSpeed(-VELOCIDADE_L);
      rightMotor.setSpeed(-VELOCIDADE_R);
    }
    
    void turnRight(){
      leftMotor.setSpeed(VELOCIDADE_L);
      rightMotor.setSpeed(VELOCIDADE_R);
    }

    void stop()
    {
      leftMotor.setSpeed(0);
      rightMotor.setSpeed(0);
      state = stateStopped;
    }

    bool doneRunning(unsigned long currentTime)
    {
      return (currentTime >= endTime);
    }

    bool obstacleAhead(unsigned int distance)
    {
      return (distance <= TOO_CLOSE);
    }

    bool turn(unsigned long currentTime)
    {
      if (random(2) == 0) {
        leftMotor.setSpeed(-VELOCIDADE_L);
        rightMotor.setSpeed(-VELOCIDADE_R);
      }
      else {
        leftMotor.setSpeed(VELOCIDADE_L);
        rightMotor.setSpeed(VELOCIDADE_R);
      }
      state = stateTurning;
      endStateTime = currentTime + random(500, 1000);
    }
    
    bool doneTurning(unsigned long currentTime)
    {
      if (currentTime >= endStateTime)
        return (sensorBackward());
      return false;
    }

    bool doneTurning(unsigned long currentTime, unsigned int distance)
    {
      if (currentTime >= endStateTime)
        return (distance > TOO_CLOSE);
      return false;
    }
    /*
        void btnParar() {
     EstadoBotao = digitalRead(BUTTON_CODE);
     if ((EstadoBotao == HIGH) && ((moving()) || (turning()))){
     stop();
     }else if((EstadoBotao == HIGH) && (stopped())){
     moveForward();
     }
     }*/

    bool sensorBackward(){ 
      return (digitalRead(9) == 0);
    }
    bool movingBackward() { 
      return (state == stateMovingBackward); 
    }
    bool movingForward() { 
      return (state == stateMovingForward); 
    }
    bool turning() { 
      return (state == stateTurning); 
    }
    bool stopped() { 
      return (state == stateStopped); 
    }

private:
    Motor leftMotor;
    Motor rightMotor;
    DistanceSensor distanceSensor;
    MovingAverage<unsigned int, 3> distanceAverage;
    enum state_t {stateStopped, stateTurning, stateMovingForward, stateMovingBackward};
    state_t state = stateMovingForward;
    int EstadoBotao = 0;
    unsigned long endStateTime;
    unsigned long endTime;
  };
};

NolramCar::Robo robo;

void setup()
{
  robo.initialize();
}

void loop()
{
  robo.run();
}


