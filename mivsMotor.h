/**
 * Motor.h
 *
 * Josh Kaplan
 * jk@joshkaplan.org
 *
 * Stepper motor control for 28BYJ-48 Stepper Motor
 */


/**
 * the Motor class provide motor control functions for 
 * interfacing the 28BYJ-48 with the Arduino Nano ATmega328 
 */

class Motor {
  public:
    Motor(int _steps, int _pin_1, int _pin_2, int _pin_3, int _pin_4);
    void rotate(float _degrees);
    void step(int _steps);
    void setSpeed(float _rpm);

  private:
    void stepMotor(int _num_steps);
    
    // motor data
    int   steps;                        // steps per revolution
    int   step_num;                     // current step
    int   step_delay;                   // based on motor speed [rpm]
    bool  direction;                    // motor direction (NOT USED for NEMA-17)

    // timing
    unsigned long last_step_time;       // time stamp [micros] of last step
  
    // motor pin numbers:
    int pin_1;
    int pin_2;
    int pin_3;
    int pin_4;  
};

