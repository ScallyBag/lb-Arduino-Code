// DIGIO16-I2C Example code
// Make all 16 lines outputs
// Blink each line, one at a time

#include <Wire.h>
#include "LandBoards_MCP23017.h"
#include "LandBoards_I2CRPT01.h"

LandBoards_MCP23017 mcp0;
LandBoards_I2CRPT01 mux;

void setup() 
{
  uint8_t port;
  
  mux.begin(0);   // start the mux
  mux.setI2CChannel(0);
  mcp0.begin(0);      // use default address 0

  for (port = 0; port < 16; port++)
    mcp0.pinMode(port, OUTPUT);
}

// flip the pin #0 up and down

void loop() 
{
  uint8_t port;

  for (port = 0; port < 16; port++)
  {
    mcp0.digitalWrite(port, HIGH);
    delay(250);
    mcp0.digitalWrite(port, LOW);
  }
}
