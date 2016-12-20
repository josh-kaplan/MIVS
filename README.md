# MIVS

The Microgravity IV System (MIVS) was my undergraduate senior design project.
The goal was to develop an IV pump that could operate in a 0g environment safely.

The team consisted of mechanical and aerospace engineers, so we took certain liberties
and made some assumptions. The biggest of these was that we ignored biology and medicine.
It was not our area of expertise, so we chose to leave out that detail and focus purely
on the mechanics of low speed fluid flow in a microgravity environment.

## Technical Design

MIVS utilized a peristaltic pump. We attempter to use both stepper motor and DC motor 
driven versions, but the final prototype used a DC motor due to ease of manufacture
and reliability. The pump used a software defined PWM approach to achieve the extremely
low speeds. The system also contained an air-in-line sensor that was used to automatically shut down 
system if air was detected.

## Control Software Details
### Libraries & Dependencies
LiquidCrystal.h     - For LCD screen functionality, comes with Arduino
DFR_Key.h           - For reading keypad buttons
LCDKeypad.h         - For reading keypad buttons (NOT USED)
mivsMotor.h         - a MIVS library for motor control

