/**
 * Air-in-line Sensor Example
 *
 * Josh Kaplan <jk@joshkaplan.org>
 * Jorge Guzman <guzmanjorgea@gmail.com>
 *
 * October 2014
 *
 * The sensor is based on the APTV resistive tracer sensor.
 * A circuit diagram can be found on page 4 of
 * http://joshkaplan.org/files/Cross-Type%20APTV.pdf
 */

#define PIN 0  
#define LED 13
#define THRESHOLD 700
int val = 0;

void setup() 
{ 
    Serial.begin(9600); 
}

void loop()
{
    // read and print value
    val = analogRead(PIN); 
    Serial.println(val);

    // if in water, turn LED on
    // otherwise, turn LED off
    if (val > THRESHOLD)                // if water
    {
        digitalWrite(LED, HIGH);
    }
    else                                // if air
    {
        digitalWrite(LED, LOW);
    }
}
