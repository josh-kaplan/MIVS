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

#define MOTOR_PIN 13              // motor PWM pin


/*----------( Air Sensor )----------*/

#define AIR_PIN 2                 // air-in-line sensor analog pin
#define THRESHOLD 800             // air sensor threshold value

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

 
 
/*----------( Global Variables )----------*/

// sensor readings
int keypad_val = 0;                     // keypad value
int knob_val = 0;                       // potentiometer knob
int air_sensor_val = 0;                 // air sensor 

// flow rate variables
float knob2flow  = 1000.0 / 1023.0;     // knob_val to motor speed conversion
float flow2delay = 1000.0;              // conversion factor - flow rate to delay time
int flow_rate = 0;                      // flow rate in mL/h
int motor_time_on  = 0;                 // motor pulse time
int motor_time_off = 0;                 // delay between motor pulses


 
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
  lcd.begin(16, 2);                // defines an LCD with 16 cols and 2 rows
  lcd.clear();                     // clears the screen
  lcd.setCursor(0, 0);             // sets the cursor to the screen origin
  keypad.setRate(10);              // sets the keypad rate (in millis I think)
  
  /*-----( MIVS Startup )-----*/
  lcd.print("Initializing...");      
  
  pinMode(MOTOR_PIN, OUTPUT);      // set motor pin as output
  motor_time_on = 40;              // set motor to pulse for 40 ms
  motor_time_off = 250;            // delay between motor pulses

  // finish setup
  lcd.print("Complete."); 
  delay(100);
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
  flow_rate = (int)round( (float)((knob_val / 1023.0) * 1000.0) );
  

  if ((air_sensor_val = analogRead(AIR_PIN)) > THRESHOLD)
  {
    //motor.setSpeed(0);
    //lcd.clear();
    //lcd.setCursor(0,0);               
    //lcd.print("Air Bubble Detected");
  }

  // print flow rate data
  lcd.setCursor(0,0);               
  lcd.print("Flow Rate:       ");
  lcd.setCursor(11,0);
  lcd.print(flow_rate);
  
  // print air sensor readings
  lcd.setCursor(0,1);               
  lcd.print("Air:         ");
  lcd.setCursor(5,1); 
  lcd.print(air_sensor_val);

  // prepare for motor pulse
  motor_time_on = 40;
  motor_time_off = (int)round( (float)(flow2delay / flow_rate) );
  Serial.println(motor_time_off);
  
  // execute a motor pulse
  digitalWrite(MOTOR_PIN, HIGH);
  delay(motor_time_on);
  digitalWrite(MOTOR_PIN, LOW);
  delay(motor_time_off);
}

