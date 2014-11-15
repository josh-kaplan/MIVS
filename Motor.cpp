/*
 * Motor.cpp
 * MIVS - Microgravity IV System
 *
 * Josh Kaplan
 * jk@joshkaplan.org
 *
 * Stepper motor control library. This library is designed for 
 * and tested with a 28BYJ-48 stepper motor.
 */

#include "Arduino.h"
#include "Motor.h"

#define CLOCKWISE false         // define motor directions
#define CCW       true


/**
 * Class constructor. Initializes data and pin outputs for user-specified 
 * Arduino wiring configuration.
 */
 
Motor::Motor(int _steps, int _pin_1, int _pin_2, int _pin_3, int _pin_4)
{
  // Motor Data
  steps      = _steps;           // steps per revolution
  step_num   = 0;                // current step 
  step_delay = 1;                // delay between stepss [micros]
  direction  = CLOCKWISE;        // motor direction

  // Time
  last_step_time = 0;            // time stamp [micros] of last step
  
  // Arduino pins used
  pin_1 = _pin_1;
  pin_2 = _pin_2;
  pin_3 = _pin_3;
  pin_4 = _pin_4;

  // Setup pins on Arduino
  pinMode(pin_1, OUTPUT);
  pinMode(pin_2, OUTPUT);
  pinMode(pin_3, OUTPUT);
  pinMode(pin_4, OUTPUT);
}


/*
 * Rotate the motor by the user specified degree value. 
 * Calls the private stepMotor function to physically control the motor.
 */
 
void Motor::rotate(float _degrees)
{
  // can only go to +/- ~5759.9 before overflowing steps_left
  // error check and return early to avoid unexpected behavior
  if (_degrees > 5000.0 || _degrees < -5000.0)
    return;                                   

  // set directon based on _degrees 
  direction  = (_degrees > 0) ? CLOCKWISE : CCW;    

  // [FIX] Is is safe to do this without typecasting?
  unsigned int steps_left = (unsigned int)round((abs(_degrees) / 360.0)*steps);  


  while (steps_left > 0)
  {   
    // Make sure there is at least 1 ms between steps
    // Let's run some more tests on this.
    // Speed control and delays will occur here
    if (micros() - last_step_time >= step_delay)
    {
      stepMotor(1);                     // take a step
      last_step_time = micros();        // store time after step
      steps_left--;                     // decrement steps remaining
    }
  }
}


/*
 * Rotate the motor by the user specified number of steps. 
 * Calls the private stepMotor function to physically control the motor.
 */
 
void Motor::step(int _steps)
{              
  // count remaining steps
  int steps_left = _steps;

  // set directon based on _degrees 
  direction  = (_steps > 0) ? CLOCKWISE : CCW;    

  // take a step an decrement steps_left
  while (steps_left > 0)
  {   
    stepMotor(1);         
    delay(step_delay);    
    steps_left--;        
  }
}


/*
 * Takes a motor speed [rpm] and sets the speed accordingly. Checks for invalid 
 * speed values (values that could result in unexpected behavior). If invalid 
 * invalid values, set motor to max speed (step, delay 1).  
 */

void Motor::setSpeed(float _rpm)
{        
  // [FIX] the max rpm val shouldn't be hard coded. 
  // check for invalid param value (14.648 is max rpm of motor)
  /*if (_rpm < 0.0 || _rpm > 30.0)
  {
    step_delay = 1000;
    return;
  }

  // calculate the delay [micros] between motor steps
  step_delay = (int)round((60 / steps) / _rpm) * 1000;
  return;*/
  step_delay = 100;
  return;
}


/*
 * Moves the motor the specified number of steps. Even though this function is
 * dynamically coded, it should only be called with a parameter of 1.
 */

void Motor::stepMotor(int _num_steps)
{
  int speed = 255;          // the speed of motor between steps
                            // always use 255 (HIGH) unless using analogwrite
  switch (step_num)
  {
    case 0:
        digitalWrite(pin_1, speed);
        digitalWrite(pin_2, 0);
        digitalWrite(pin_3, speed);
        digitalWrite(pin_4, 0);
        break;
    case 1:
        digitalWrite(pin_1, 0);
        digitalWrite(pin_2, speed);
        digitalWrite(pin_3, speed);
        digitalWrite(pin_4, 0);
        break;
    case 2:
        digitalWrite(pin_1, 0);
        digitalWrite(pin_2, speed);
        digitalWrite(pin_3, 0);
        digitalWrite(pin_4, speed);
        break;
    case 3:
        digitalWrite(pin_1, speed);
        digitalWrite(pin_2, 0);
        digitalWrite(pin_3, 0);
        digitalWrite(pin_4, speed);
        break;
    default:
      digitalWrite(pin_1, 0);
      digitalWrite(pin_2, 0);
      digitalWrite(pin_3, 0);
      digitalWrite(pin_4, 0);
      break;        
  }
  
  step_num += (direction) ? -1 : 1;
  
  if ( !(step_num >= 0 && step_num <= 3) )  // if steps is not between 0 and 3
    step_num = (step_num > 3) ? 0 : 3;      // ensure steps between 0 and 3

}

