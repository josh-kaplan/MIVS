/*
 * MIVS - Microgravity IV System
 * Fall 2014
 *
 * Josh Kaplan
 * jk@joshkaplan.org
 *
 * Using 28BYJ-48 Stepper Motor with Arduino Nano (ATmega328)
 * Based on http://www.instructables.com/id/BYJ48-Stepper-Motor/?ALLSTEPS
 */

#include <LiquidCrystal.h>

//#include "LCDKeypad.h"
#include "DFR_Key.h"

// include motor library
#include "Motor.h"

// motor pin definitions
#define IN1  3
#define IN2  11
#define IN3  12
#define IN4  13

// steps per revolution 
#define STEPS 200

// construct motor object
Motor motor(STEPS, IN1, IN2, IN3, IN4);

// Sainsmart LCD Keypad Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

// Sainsmart LCD Keypad
DFR_Key keypad;
 
// globals
int localKey = 0;                   // keypad value
float motor_speed = 14.6;           // motor speed (defaults to max speed)



/*
 * the setup() function runs once at the beginning of the program.
 */

void setup()
{
  Serial.begin(115200);

  // LCD set up
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MIVS v6.0");
  delay(2500);
  keypad.setRate(10);
}


/*
 * the loop() function repeats infinitely.
 */

void loop()
{

  motor.setSpeed(motor_speed);        // half speed
  motor.rotate(360.0);                // one rotation cw
  //delay(500);                         // pause
  
  localKey = keypad.getKey();

  

  if (localKey == 3)
  {
    motor_speed += 0.1;
    motor.setSpeed(motor_speed);
  }
  else if (localKey == 4)
  {
    motor_speed -= 0.1;
    motor.setSpeed(motor_speed);
  }
  
  if (localKey != SAMPLE_WAIT)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed:");
    lcd.setCursor(8, 0);
    lcd.print(motor_speed);
    lcd.setCursor(0, 1);
    lcd.print(localKey);
  }



}

