/*
 * MLCD IO Example
 * Fall 2014
 *
 * Josh Kaplan
 * jk@joshkaplan.org
 *
 * Read from button  and print to screen example.
 */

#include <LiquidCrystal.h>
#include "DFR_Key.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
DFR_Key keypad;

int localKey = 0;               

void setup()
{
  Serial.begin(115200);

  // LCD set up
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);;
  delay(500);
  keypad.setRate(10);
}

void loop()
{  
  localKey = keypad.getKey();
 
  if (localKey != SAMPLE_WAIT)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(localKey);
  }
}

