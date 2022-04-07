/////////////////////////////////////////////////////////////////////////////////////////////////
// D128LibExample code
// Make all 128 lines outputs
// Blink each line, one at a time
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <LandBoards_Digio128_64.h>

LandBoards_Digio128_64 Dio128;		// Call the class constructor for the DigIO-128 card

/////////////////////////////////////////////////////////////////////////////////////////////////
// setup() - Initialize the card
/////////////////////////////////////////////////////////////////////////////////////////////////

void setup(void)
{
  Dio128.begin();              // connects to the 8 MCP23017 parts
  TWBR = 12;                   // go to 400 KHz I2C speed mode
  for (uint8_t pin = 0; pin < 64; pin++)
    Dio128.pinMode(pin, INPUT);    // make all pins into INPUTs
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// flip the pin #0 up and down
/////////////////////////////////////////////////////////////////////////////////////////////////

void loop(void)
{
  for (uint8_t pin = 0; pin < 64; pin++)    // bounce an LED through all the channels
  {
    Dio128.digitalWrite(pin, HIGH);
    delay(100);
    Dio128.digitalWrite(pin, LOW);
  }
  Dio128.writeGPIOAB(0,0x5555);              // write alternate bits
  delay(1000);
  Dio128.writeGPIOAB(0,~Dio128.readGPIOAB(0));  // alternate the bits
  delay(1000);
}

