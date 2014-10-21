/**
 * Potentiometer Read Example 
 *
 * Josh Kaplan <jk@joshkaplan.org>
 * October 20, 2014
 *
 * See wiring diagram at http://www.arduino.cc/en/tutorial/potentiometer
 */
 
int pin = 1;                 // potentiometer analog read pin
int val = 0;                 // variable to store data

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  val = analogRead(pin);      // read the value from the sensor
  Serial.println(val);        // print data to monitor
}
