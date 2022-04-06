//////////////////////////////////////////////////////////////////////////////
// MenuCodeOps() - Run the OptoOut8-I2C card tests
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

void testDIGIO16board(void)
{
  int pass1Fail0;
  int testPass = 0;
  menuCard.setLED(0, HIGH);
  do
  {
    //    int testBit = 0x1;
    uint8_t port;
    u8g.firstPage();
    do
    {
      setDisplayCursor(0, 0);
      u8g.print("Dio128 Test");
      setDisplayCursor(1, 0);
      u8g.print("Loops=");
      u8g.print(passCount);
      setDisplayCursor(2, 0);
      setDisplayCursor(3, 0);
      u8g.print("Any to return");
    }
    while ( u8g.nextPage() );

    for (port = 0; port < 16; port++)
    {
      mcp0.digitalWrite(port, HIGH);
      menuCard.delayAvailable(250);
      mcp0.digitalWrite(port, LOW);
    }
    passCount++;
    menuCard.delayAvailable(100);
  }
  while (menuCard.pollKeypad() == NONE);
  testCount = 0;
  passCount = 0;
  failCount = 0;
  menuCard.setLED(0, LOW);
  return;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//

void readEEPROM(void)
{
  char readBuff[97];
  readBuff[96] = 0;
  eeprom.begin();
  eep_vals myEep;
  menuCard.setLED(1, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Reading EEPROM");
    eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

    setDisplayCursor(1, 0);
    for (int loopv = 0; loopv < 4; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(2, 0);
    for (int loopv = 32; loopv < 44; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(3, 0);
    for (int loopv = 64; loopv < 76; loopv++)
      u8g.print(readBuff[loopv]);
  }
  while ( u8g.nextPage() );
  while (menuCard.pollKeypad() == NONE);
  menuCard.setLED(1, LOW);
}

//////////////////////////////////////////////////////////////////////////////
// writeEEPROM()
//////////////////////////////////////////////////////////////////////////////

void writeEEPROM(void)
{
  char readBuff[97];
  readBuff[96] = 0;
  eeprom.begin();
  eep_vals myEep;
  menuCard.setLED(1, HIGH);
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print("Writing EEPROM");
    myEep.signature[0] = 'O';
    myEep.signature[1] = 'D';
    myEep.signature[2] = 'A';
    myEep.signature[3] = 'S';
    myEep.fmt_version = 0x01;
    myEep.rsvd = 0;
    myEep.numatoms = 0x2;
    myEep.eeplen = 96;
    myEep.uuid[0] = '0';  // Serial number
    myEep.uuid[1] = '0';
    myEep.uuid[2] = '0';
    myEep.uuid[3] = '0';
    myEep.uuid[4] = '0';
    myEep.uuid[5] = '0';
    myEep.uuid[6] = '0';
    myEep.uuid[7] = '0';
    myEep.uuid[8] = '0';
    myEep.uuid[9] = '0';
    myEep.uuid[10] = '0';
    myEep.uuid[11] = '0';
    myEep.uuid[12] = '0';
    myEep.uuid[13] = '0';
    myEep.uuid[14] = '0';
    myEep.uuid[15] = '0';
    myEep.pid = 0x04;
    myEep.vslen = 32;
    myEep.pslen = 32;
    strcpy(myEep.vstr, "land-boards.com");
    strcpy(myEep.pstr, "DigIO16-I2C");

    eeprom.writeBlock(0, (uint8_t*) myEep.signature, 96);
    delay(10);

    eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

    setDisplayCursor(1, 0);
    for (int loopv = 0; loopv < 4; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(2, 0);
    for (int loopv = 32; loopv < 44; loopv++)
      u8g.print(readBuff[loopv]);
    setDisplayCursor(3, 0);
    for (int loopv = 64; loopv < 76; loopv++)
      u8g.print(readBuff[loopv]);
  }
  while ( u8g.nextPage() );
  while (menuCard.pollKeypad() == NONE);
  menuCard.setLED(1, LOW);
}

void testButtons(void)
{
  uint8_t keyState;
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Button tests"));
    setDisplayCursor(1, 0);
    u8g.print(F("Press button"));
    setDisplayCursor(2, 0);
    u8g.print(F("Select=exit"));
  }
  while ( u8g.nextPage() );
  do
  {
    delay(100);
    keyState = menuCard.pollKeypad();
    switch (keyState)
    {
      case RIGHT:
        printString("Right button");
        break;
      case LEFT:
        printString("Left Button");
        break;
      case UP:
        printString("Up button");
        break;
      case DOWN:
        printString("Down button");
        break;
    }
  }
  while (keyState != SELECT);
}

void printString(char * myString)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(myString);
  }
  while ( u8g.nextPage() );
}

void testLEDsFcn(void)
{
  u8g.firstPage();
  do
  {
    setDisplayCursor(0, 0);
    u8g.print(F("Running"));
    setDisplayCursor(1, 0);
    u8g.print(F("LED Tests"));
  }
  while ( u8g.nextPage() );
  menuCard.setLED(0, HIGH);
  delay(500);
  menuCard.setLED(0, LOW);
  menuCard.setLED(1, HIGH);
  delay(500);
  menuCard.setLED(1, LOW);
  menuCard.setLED(2, HIGH);
  delay(500);
  menuCard.setLED(2, LOW);
}
