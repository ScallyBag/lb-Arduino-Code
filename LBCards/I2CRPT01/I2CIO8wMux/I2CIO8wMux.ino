// I2CIO8wMux Example code
// Blink each line, one at a time

#include <Wire.h>
#include <LandBoards_I2CIO8.h>
#include "LandBoards_I2CRPT01.h"

LandBoards_I2CIO8 myI2CIO8;
LandBoards_I2CRPT01 mux;

void setup() 
{
  uint8_t port;
  
  mux.begin(0);   // start the mux
  mux.setI2CChannel(0);
  myI2CIO8.begin(0);      // use default address 0

  for (port = 0; port < 4; port++)
    myI2CIO8.pinMode(port, OUTPUT);
}

// flip the pin #0 up and down

void loop() 
{
  uint8_t port;

  for (port = 0; port < 4; port++)
  {
    myI2CIO8.writeLED(port, HIGH);
    delay(250);
    myI2CIO8.writeLED(port, LOW);
  }
}
