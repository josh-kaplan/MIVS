/** 
 * Rotary Encoder Example 1
 *
 * Josh Kaplan <jk@joshkaplna.org>
 * November 9, 2014
 * 
 * -------------------------------------------------------------------
 * Source: http://playground.arduino.cc/Main/RotaryEncoders#Example1
 *
 * Read Quadrature Encoder
 * Connect Encoder to Pins encoder0PinA, encoder0PinB, and +5V.
 *
 * Sketch by max wolf / www.meso.net
 * v. 0.1 - very basic functions - mw 20061220
 *
 */  


int val; 
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup() 
{ 
    pinMode (encoder0PinA,INPUT);
    pinMode (encoder0PinB,INPUT);
    Serial.begin (9600);
} 

void loop() 
{ 
    n = digitalRead(encoder0PinA);
    if ((encoder0PinALast == LOW) && (n == HIGH)) 
    {
        encoder0Pos += (digitalRead(encoder0PinB) == LOW) ? -1 : 1;
        
        Serial.println (encoder0Pos);
    } 
    encoder0PinALast = n;
    delay(100);
} 