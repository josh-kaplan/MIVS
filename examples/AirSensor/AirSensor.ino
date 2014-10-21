/**
 * Air-in-line Sensor Example
 *
 * Josh Kaplan <jk@joshkaplan.org>
 * Jorge Guzman <guzmanjorgea@gmail.com>
 *
 * October 2014
 *
 * The sensor is based on the APTV resistive tracer sensor.
 * A circuit diagram can be found aon page 4 of
 * http://joshkaplan.org/files/Cross-Type%20APTV.pdf
 */

int analogPin = 0;    
int val = 0;                        // variable to store the value read

void setup()
{
  Serial.begin(9600);               //  setup serial
}


void loop()
{
  val = analogRead(analogPin);      // read the input pin
  Serial.println(val);              // print value to monitor
}