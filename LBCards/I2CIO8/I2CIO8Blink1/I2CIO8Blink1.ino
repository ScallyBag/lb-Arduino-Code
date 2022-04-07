//

#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp;

void setup()
{
  mcp.begin();      // use default address 0
  for (int loopCnt = 0; loopCnt < 4; loopCnt++)
    mcp.pinMode(loopCnt, OUTPUT);
}

//

void loop()
{
  mcp.digitalWrite(0, HIGH);
  delay(500);
  mcp.digitalWrite(0, LOW);
  delay(500);
}
