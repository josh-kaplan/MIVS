/*
 
 L9110 motor driver controlling 2 small DC motors 
 */
 
const int AIA = 9;  // (pwm) pin 9 connected to pin A-IA 
const int AIB = 5;  // (pwm) pin 5 connected to pin A-IB 
const int BIA = 10; // (pwm) pin 10 connected to pin B-IA  
const int BIB = 6;  // (pwm) pin 6 connected to pin B-IB
int current_step = 1;
int step_delay = 10;
 
byte speed = 255;  // change this (0-255) to control the speed of the motors 
 
void setup() {
  Serial.begin(9600);
  pinMode(AIA, OUTPUT); // set pins to output
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}
 
void loop() 
{
  switch (current_step)
  {
    case 1:
        analogWrite(AIA, speed);
        analogWrite(AIB, 0);
        analogWrite(BIA, speed);
        analogWrite(BIB, 0);
        break;
    case 2:
        analogWrite(AIA, 0);
        analogWrite(AIB, speed);
        analogWrite(BIA, speed);
        analogWrite(BIB, 0);
        break;
    case 3:
        analogWrite(AIA, 0);
        analogWrite(AIB, speed);
        analogWrite(BIA, 0);
        analogWrite(BIB, speed);
        break;
    case 4:
        analogWrite(AIA, speed);
        analogWrite(AIB, 0);
        analogWrite(BIA, 0);
        analogWrite(BIB, speed);
        break;
    default:
        analogWrite(AIA, 0);
        analogWrite(AIB, 0);
        analogWrite(BIA, 0);
        analogWrite(BIB, 0);
        break;        
  }
  
  current_step++;
  
  if (current_step > 4) 
    current_step = 1; 

  delay(step_delay);
}
 

 
