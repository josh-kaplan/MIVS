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
  direction  = CLOCKWISE;        // motor direction (NOT USED with NEMA-17)

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


  while (steps_left > 0)
  {   
    stepMotor(1);         // take one step
    delay(step_delay);    // delay
    steps_left--;         // decrement steps remaining
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
  if (_rpm < 0.0 || _rpm > 14.648)
  {
    step_delay = 1000;
    return;
  }

  // calculate the delay [micros] between motor steps
  step_delay = (int)round((60000 / steps) / _rpm) * 1000;
  return;
}


/*
 * Moves the motor the specified number of steps. Even though this function is
 * dynamically coded, it should only be called with a parameter of 1.
 */

void Motor::stepMotor(int _num_steps)
{
  int speed = 255;          // the speed of motor between steps

  switch (step_num)
  {
    case 0:
      analogWrite(AIA, speed);
      analogWrite(AIB, 0);
      analogWrite(BIA, speed);
      analogWrite(BIB, 0);
      break;

    case 1:
      analogWrite(AIA, 0);
      analogWrite(AIB, speed);
      analogWrite(BIA, speed);
      analogWrite(BIB, 0);
      break;

    case 2:
      analogWrite(AIA, 0);
      analogWrite(AIB, speed);
      analogWrite(BIA, 0);
      analogWrite(BIB, speed);
      break;

    case 3:
      analogWrite(AIA, speed);
      analogWrite(AIB, 0);
      analogWrite(BIA, 0);
      analogWrite(BIB, speed);
      break;

    default:
      analogWrite(AIA, 0);
      analogWrite(AIB, 0);
      analogWrite(BIA, 0);
      analogWrite(BIB, 0);
      break;        
}
  
  step_num += (direction) ? -1 : 1;
  
  if ( !(step_num >= 0 && step_num <= 3) )  // if steps is not between 0 and 3
    step_num = (step_num > 3) ? 0 : 3;      // ensure steps between 0 and 3
}

