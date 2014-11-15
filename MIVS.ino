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

/*----------( Libraries )----------*/

#include <LiquidCrystal.h>        // Arduino LCD library for LCD screen
//#include "LCDKeypad.h"
#include "DFR_Key.h"              // library for reading keypad values
#include "Motor.h"                // motor library for stepper motor


/*----------( Motor Setup )----------*/

#define AIA  13                    // motor pin definitions
#define AIB  12
#define BIA  11
#define BIB  3

#define STEPS 200                 // steps per revolution


/*----------( Air Sensor )----------*/

#define AIR_PIN 2                 // air-in-line sensor analog pin

/*----------( UI Setup)----------*/

#define LCD_1 8                   // define LCD pins
#define LCD_2 9
#define LCD_3 4
#define LCD_4 5
#define LCD_5 6
#define LCD_6 7

#define KNOB_PIN 3                // define control knob analog pin


/*----------( Object Declarations )----------*/

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);       // Sainsmart LCD Keypad Shield
DFR_Key keypad;                            // Sainsmart LCD Keypad
Motor motor(STEPS, AIA, AIB, BIA, BIB);    // construct motor object

 
 
/*----------( Global Variables )----------*/

// sensor readings
int keypad_val = 0;                     // keypad value
int knob_val = 0;                       // potentiometer knob
int air_sensor_val = 0;                 // air sensor 

float conversion_factor = 1.0;          // knob_val to motor speed conversion
float flow_rate = 0;                    // flow rate in mL/h
float motor_speed = 0;                  // motor speed (defaults to max speed)

 
/**
 * ------------------------------------------------------------
 * Setup
 * ------------------------------------------------------------
 *
 * the setup() function runs once at the beginning of the program.
 */
void setup()
{
  Serial.begin(9600);
  
  // LCD set up
  lcd.begin(16, 2);                // defines an LCD screen with 16 columns and 2 rows
  lcd.clear();                     // clears the screen
  lcd.setCursor(0, 0);             // sets the cursor to the screen origin
  keypad.setRate(10);              // sets the keypad rate (in millis I think)
  
  // MIVS Startup
  lcd.print("Loading..."); 
  Serial.println("Loading...");      
  
  lcd.print("MIVS Started."); 
  Serial.println("MIVS Started.");
  delay(500);
  lcd.clear();
}


/**
 * ------------------------------------------------------------
 * Loop
 * ------------------------------------------------------------
 *
 * the loop() function repeats infinitely.
 */
void loop()
{
  // read speed setting, print to screen, set flow rate
  knob_val = analogRead(KNOB_PIN);
  flow_rate = (float) knob_val * conversion_factor;
  

  if ((air_sensor_val = analogRead(AIR_PIN)) > 900 )
  {
    //motor.setSpeed(0);
    //lcd.clear();
    //lcd.setCursor(0,0);               
    //lcd.print("Air Bubble Detected");
  }

  lcd.setCursor(0,0);               
  lcd.print("Flow Rate: ");
  lcd.setCursor(11,0);
  lcd.print(flow_rate);
  
  lcd.setCursor(0,1);               
  lcd.print("Air:        ");
  lcd.setCursor(6,1); 
  lcd.print(air_sensor_val);

  
  //motor.setSpeed(motor_speed);        // in rpm
  //motor.step(200);                    // rotate a number of steps
  //
  
  // uncomment the line below for testing
  delay(100);
}

