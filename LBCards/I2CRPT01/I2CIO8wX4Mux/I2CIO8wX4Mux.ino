// I2CIO8wMux Example code
// Blink each line, one at a time

#include <Wire.h>
#include <LandBoards_I2CIO8.h>
#include "LandBoards_I2CRPT01.h"

LandBoards_I2CIO8 myI2CIO80;
LandBoards_I2CIO8 myI2CIO81;
LandBoards_I2CIO8 myI2CIO82;
LandBoards_I2CIO8 myI2CIO83;

LandBoards_I2CRPT01 mux;

void setup()
{
  uint8_t port;

  mux.begin(0);   // start the mux
  mux.setI2CChannel(0);
  myI2CIO80.begin(0);      // use default address 0
  mux.setI2CChannel(1);
  myI2CIO81.begin(0);      // use default address 0
  mux.setI2CChannel(2);
  myI2CIO82.begin(0);      // use default address 0
  mux.setI2CChannel(3);
  myI2CIO83.begin(0);      // use default address 0
}

// flip the pin #0 up and down

void loop()
{
  uint8_t port;

  mux.setI2CChannel(0);
  for (port = 0; port < 4; port++)
  {
    myI2CIO80.writeLED(port, HIGH);
    delay(250);
    myI2CIO80.writeLED(port, LOW);
  }
  mux.setI2CChannel(1);
  for (port = 0; port < 4; port++)
  {
    myI2CIO81.writeLED(port, HIGH);
    delay(250);
    myI2CIO81.writeLED(port, LOW);
  }
  mux.setI2CChannel(2);
  for (port = 0; port < 4; port++)
  {
    myI2CIO82.writeLED(port, HIGH);
    delay(250);
    myI2CIO82.writeLED(port, LOW);
  }
  mux.setI2CChannel(3);
  for (port = 0; port < 4; port++)
  {
    myI2CIO83.writeLED(port, HIGH);
    delay(250);
    myI2CIO83.writeLED(port, LOW);
  }
}

