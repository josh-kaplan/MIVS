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

int knob_val = 0;                       // potentiometer knob
float c_1 = 1000.0 / 1023.0;     // knob_val to flow rate conversion
float c_2 = 100000.0;              // flow rate to time delay conversion
int flow_rate = 0;               // flow rate in mL/h
int motor_time_off = 0;          // delay between motor pulses


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // calculate and prinf flow rate
  flow_rate = (int)round( c_1 * (float)knob_val );
  Serial.print("Flow Rate:  ");
  Serial.println(flow_rate);

  motor_time_off = 1000 - flow_rate;
  Serial.print("Time Delay: ");
  Serial.println(motor_time_off);
  Serial.println("");
  delay(100);

  knob_val++;
  
  // execute a motor pulse
  //digitalWrite(MOTOR_PIN, HIGH);
  //delay(motor_time_on);
  //digitalWrite(MOTOR_PIN, LOW);
  //delay(motor_time_off);
}

