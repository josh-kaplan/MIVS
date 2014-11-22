/*
 
 L9110 motor driver controlling 2 small DC motors 
 */
 // 9 5 10 6
const int pin_1 = 3;  // (pwm) pin 9 connected to pin A-IA 
const int pin_2 = 4;  // (pwm) pin 5 connected to pin A-IB 
const int pin_3 = 5; // (pwm) pin 10 connected to pin B-IA  
const int pin_4 = 6;  // (pwm) pin 6 connected to pin B-IB

int current_step = 1;
int step_delay = 10;
 
byte speed = 255;  // change this (0-255) to control the speed of the motors 
 
void setup() 
{
  Serial.begin(9600);
  pinMode(pin_1, OUTPUT); // set pins to output
  pinMode(pin_2, OUTPUT);
  pinMode(pin_3, OUTPUT);
  pinMode(pin_4, OUTPUT);
}
 
void loop() 
{
  switch (current_step)
  { 
    case 0:
        digitalWrite(pin_1, speed);
        digitalWrite(pin_2, 0);
        digitalWrite(pin_3, speed);
        digitalWrite(pin_4, 0);
        break;
    case 1:
        digitalWrite(pin_1, 0);
        digitalWrite(pin_2, speed);
        digitalWrite(pin_3, speed);
        digitalWrite(pin_4, 0);
        break;
    case 2:
        digitalWrite(pin_1, 0);
        digitalWrite(pin_2, speed);
        digitalWrite(pin_3, 0);
        digitalWrite(pin_4, speed);
        break;
    case 3:
        digitalWrite(pin_1, speed);
        digitalWrite(pin_2, 0);
        digitalWrite(pin_3, 0);
        digitalWrite(pin_4, speed);
        break;
    default:
      digitalWrite(pin_1, 0);
      digitalWrite(pin_2, 0);
      digitalWrite(pin_3, 0);
      digitalWrite(pin_4, 0);
      break;        
  }
  
  current_step++;
  
  if (current_step > 4) 
    current_step = 1; 

  delay(step_delay);
}
 

 
