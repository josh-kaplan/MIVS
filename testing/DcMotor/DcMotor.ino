/**
 * High End Flow Rate Test
 *
 * Josh Kaplan <jk@joshkaplan.org>
 * November 11, 2014
 * 
 * A routine for automated test of the high end flow rate.
 */

// pin definitions
int mPin = 11;                    // motor pin
int led = 13;                     

// data storage
int counter = 0;
int incomingByte = 0;
unsigned int end_time = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(mPin, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  // turn motor and LED on, with a delay of 250 ms
  digitalWrite(mPin, 255);      
  digitalWrite(led, HIGH);      
  delay(500);                   
  
  // read user data
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    if (incomingByte == 's')
    {
      // shutdown pump end record time
      digitalWrite(mPin, 0);        
      digitalWrite(led, LOW);       
      end_time = millis();

      // print results
      Serial.println("------------------------------");
      Serial.println("TEST ENDED");
      Serial.println("------------------------------");
      Serial.print("Loops: ");
      Serial.println(counter);
      Serial.print("Time: ");
      Serial.println(end_time);
      while (1) {}
    }
  }  
  
  counter++;                   // increment counter
  Serial.println(counter);     // print counter to screen
}

