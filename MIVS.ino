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


/*----------( Pin Definitions )----------*/
#define MOTOR_PIN 13              // motor PWM pin
#define AIR_PIN 2                 // air-in-line sensor analog pin
#define KNOB_PIN 3                // define control knob analog pin

/*----------( Controls )----------*/
#define THRESHOLD 800             // air sensor threshold value

/*----------( LCD Setup )----------*/
#define LCD_1 8                   
#define LCD_2 9
#define LCD_3 4
#define LCD_4 5
#define LCD_5 6
#define LCD_6 7

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);       // Sainsmart LCD Keypad Shield
 
 
/*----------( Global Variables )----------*/

// sensor readings
int knob_val = 0;                       // potentiometer knob
int air_sensor_val = 0;                 // air sensor 

// flow rate variables
float c_1 = 1000.0 / 1023.0;            // knob_val to flow rate conversion
int flow_rate = 0;                      // flow rate in mL/h
unsigned int motor_time_on  = 0;        // motor pulse time
unsigned int motor_time_off = 0;        // delay between motor pulses

 
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

  /*-----( MIVS Startup )-----*/
  lcd.print("Initializing...");      

  pinMode(MOTOR_PIN, OUTPUT);      // set motor pin as output

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Microgravity");
  lcd.setCursor(0, 1);
  lcd.print("Medical"); 
  delay(2000);
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

  // calculate and prinf flow rate
  flow_rate = (int)round( c_1 * (float)knob_val );
  Serial.print("Flow Rate:  ");
  Serial.println(flow_rate);
  lcd.setCursor(0,0);               
  lcd.print("Flow Rate:       ");
  lcd.setCursor(11,0);
  lcd.print(flow_rate);

  // read air sensor value, report failure if bubble detected
  if ((air_sensor_val = analogRead(AIR_PIN)) > THRESHOLD)
  {
    //lcd.clear();
    //lcd.setCursor(0,0);               
    //lcd.print("Air Bubble Detected");

    // stop the pump
    //while (1) {};       
  }

  // print air sensor readings
  lcd.setCursor(0,1);               
  lcd.print("Air:         ");
  lcd.setCursor(5,1); 
  lcd.print(air_sensor_val);



  // prepare for motor pulse
  motor_time_on = 40;
  motor_time_off = 1000 - flow_rate;
  Serial.print("Time Delay: ");
  Serial.println(motor_time_off);
  Serial.println("");

  
  // execute a motor pulse
  digitalWrite(MOTOR_PIN, (flow_rate) ? HIGH : LOW);
  delay(motor_time_on);
  if (flow_rate != 1000)
  {
    digitalWrite(MOTOR_PIN, LOW);
    delay(motor_time_off);
  }
}

