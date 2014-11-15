/**
 * High End Flow Rate Test
 *
 * Josh Kaplan <jk@joshkaplan.org>
 * November 11, 2014
 * 
 * A routine for automated test of the high end flow rate.
 */

#define DELAY_ON  200              // time motor is on
#define DELAY_OFF 250             // time motor is off
#define NUM_PULSES 500


int mPin    = 13;                 // motor pin
int led     = 13;                 // built in LED
int counter = 0;                  // loop counter


/**
 * ---------------------------------------
 * Setup
 * ---------------------------------------
 * The setup runs once and only once. It is used to 
 * initialize pins and perform other initial setup.
 */
void setup()
{
  Serial.begin(9600);
  pinMode(mPin, OUTPUT);
  pinMode(led, OUTPUT);
}

/**
 * ---------------------------------------
 * Loop
 * ---------------------------------------
 * The loop repeats infinitely. This is where the main 
 * functionality of the code is. 
 */
void loop()
{
  // turn motor and LED on, followed by a delay
  digitalWrite(mPin, 255);      
  digitalWrite(led, HIGH);      
  delay(DELAY_ON);  

  // turn the motor and LED off, followed by a delay
  digitalWrite(mPin, 0);      
  digitalWrite(led, LOW);      
  delay(DELAY_OFF);  

  while (counter >= NUM_PULSES) {}
  
  counter++;                   // increment counter
  Serial.println(counter);     // print counter to screen
  
}

