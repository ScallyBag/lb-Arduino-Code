/*
  DIGIO16I2C_DigitalReadSerial

  Reads digital input bit 0 from DIGIO16 and prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

// digital pin has a pushbutton attached to it. Give it a name:

#include "LandBoards_MCP23017.h"

LandBoards_MCP23017 mcp0;

#define BIT_TO_READ 0

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  mcp0.begin(0);
  mcp0.pinMode(BIT_TO_READ,INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() 
{
  // read the input pin:
  int pinState = mcp0.digitalRead(BIT_TO_READ);
  // print out the state of the button:
  Serial.println(pinState);
  delay(1);        // delay in between reads for stability
}
