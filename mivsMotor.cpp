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
  step_delay = 1;                // motor speed [rpm]
  direction  = CLOCKWISE;        // motor direction

  // Time
  last_step_time = 0;            // time stamp [microseconds] of last step
  
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
 * Rotate the motor by the user specified number of steps. 
 * Calls the private stepMotor function to physically controll the motor.
 */

void Motor::rotate(float _degrees)
{
  // can only go to +/- ~5759.9 before overflowing steps_left
  // error check and return early to avoid unexpected behavior
  if (_degrees > 5750.0 || _degrees < -5750.0)
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
 * Takes a motor speed [rpm] and sets the speed accordingly. Checks for invalid 
 * speed values (values that could result in unexpected behavior). If invalid 
 * invalid values, set motor to max speed (step, delay 1).  
 */

void Motor::setSpeed(float _rpm)
{        
  // check for invalid param value (14.648 is max rpm of motor)
  if (_rpm < 0.0 || _rpm > 14.648)
  {
    step_delay = 1000;
    return;
  }

  // calculate the delay [ms] between motor steps
  step_delay = (int)round((60000 / 4096) / _rpm) * 1000;
  return;
}


/*
 * Moves the motor the specified number of steps. Even though this function is
 * dynamically coded, it should only be called with a parameter of 1.
 */

void Motor::stepMotor(int _num_steps)
{
  for (int i = 0; i < _num_steps; i++)
  {
    switch (step_num)
    {
     case 0:
       digitalWrite(pin_1, LOW); 
       digitalWrite(pin_2, LOW);
       digitalWrite(pin_3, LOW);
       digitalWrite(pin_4, HIGH);
       break; 
     case 1:
       digitalWrite(pin_1, LOW); 
       digitalWrite(pin_2, LOW);
       digitalWrite(pin_3, HIGH);
       digitalWrite(pin_4, HIGH);
       break; 
     case 2:
       digitalWrite(pin_1, LOW); 
       digitalWrite(pin_2, LOW);
       digitalWrite(pin_3, HIGH);
       digitalWrite(pin_4, LOW);
       break; 
     case 3:
       digitalWrite(pin_1, LOW); 
       digitalWrite(pin_2, HIGH);
       digitalWrite(pin_3, HIGH);
       digitalWrite(pin_4, LOW);
       break; 
     case 4:
       digitalWrite(pin_1, LOW); 
       digitalWrite(pin_2, HIGH);
       digitalWrite(pin_3, LOW);
       digitalWrite(pin_4, LOW);
       break; 
     case 5:
       digitalWrite(pin_1, HIGH); 
       digitalWrite(pin_2, HIGH);
       digitalWrite(pin_3, LOW);
       digitalWrite(pin_4, LOW);
       break; 
     case 6:
       digitalWrite(pin_1, HIGH); 
       digitalWrite(pin_2, LOW);
       digitalWrite(pin_3, LOW);
       digitalWrite(pin_4, LOW);
       break; 
     case 7:
       digitalWrite(pin_1, HIGH); 
       digitalWrite(pin_2, LOW);
       digitalWrite(pin_3, LOW);
       digitalWrite(pin_4, HIGH);
       break; 
     default:
       digitalWrite(pin_1, LOW); 
       digitalWrite(pin_2, LOW);
       digitalWrite(pin_3, LOW);
       digitalWrite(pin_4, LOW);
       break; 
    }
    
    step_num += (direction) ? 1 : -1;           // increment/decrement steps 
                                                // based on direction

    if ( !(step_num >= 0 && step_num <= 7) )    // if steps is not between 0 and 7
      step_num = (step_num > 7) ? 0 : 7;        // ensure steps stays between 0 and 7
  }
}

