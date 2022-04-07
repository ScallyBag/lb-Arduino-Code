//////////////////////////////////////////////////////////
// void eepromRead(void)
// http://land-boards.com/blwiki/index.php?title=DIGIO-128
//////////////////////////////////////////////////////////

void eepromRead(void)
{
  char readBuff[97];
  readBuff[96] = 0;
  Serial.println("Reading EEPROM");
  delay(10);

  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

  Serial.print("Family=");
  for (int loopv = 0; loopv < 4; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print("Company=");
  for (int loopv = 32; loopv < 48; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print("Product=");
  int loopv = 64;
  do
  {
    Serial.print(readBuff[loopv++]);
  }
  while ((readBuff[loopv] != 0) && (loopv < 128));
  Serial.println("");
}

//////////////////////////////////////////////////////////
// void eepromCheck(void)
//////////////////////////////////////////////////////////

uint8_t eepromCheck(void)
{
  char testStr[33];
  char readBuff[97];
  readBuff[96] = 0;
  Serial.print("Checking EEPROM...");

  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

//  Serial.print("Testing Family...");
  for (int loopv = 0; loopv < 4; loopv++)
  {
    testStr[loopv] = readBuff[loopv];
  }
  testStr[4] = 0;
  if (strcmp(testStr, "ODAS") != 0)
  {
//    Serial.println("Family Mismatch");
    return 1;
  }
//  else
//    Serial.println("Family match");
//  Serial.print("Testing Company...");
  for (int loopv = 32; loopv < 48; loopv++)
    testStr[loopv - 32] = readBuff[loopv];
  testStr[33] = 0;
  if (strcmp(testStr, "land-boards.com") != 0)
  {
//    Serial.println("Company Mismatch");
    return 1;
  }
//  else
//    Serial.println("Company match");
//  Serial.print("Testing Product ID...");
  int loopv = 64;
  do
  {
    testStr[loopv - 64] = readBuff[loopv];
    loopv++;
  }
  while ((readBuff[loopv] != 0) && (loopv < 128));
  testStr[loopv - 64] = 0;
  if (strcmp(testStr, "DIGIO-128") != 0)
  {
//    Serial.println(testStr);
//    Serial.println("ProductID Mismatch");
    return 1;
  }
//  else
//    Serial.println("Match");
  return 0;
}

//////////////////////////////////////////////////////////
// eepromWrite()
//////////////////////////////////////////////////////////

void eepromWrite(void)
{
  char readBuff[97];
  readBuff[96] = 0;
  Serial.println("Writing EEPROM");
  eeprom.begin();
  eep_vals myEep;

  Serial.println("Initializing eep buffer");
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
  myEep.pid = 0x02;
  myEep.vslen = 32;
  myEep.pslen = 32;
  strcpy(myEep.vstr, "land-boards.com");
  strcpy(myEep.pstr, "DIGIO-128");

  Serial.print("len of buffer=");
  Serial.println(sizeof(myEep));

  eeprom.writeBlock(0, (const uint8_t*) myEep.signature, 96);
  Serial.println("reading block");
  delay(10);

  eeprom.readBlock((const uint16_t) 0, (unsigned char*) readBuff, (const uint16_t) 96);

  Serial.print("Family=");
  for (int loopv = 0; loopv < 4; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print("Company=");
  for (int loopv = 32; loopv < 48; loopv++)
    Serial.print(readBuff[loopv]);
  Serial.println("");
  Serial.print("Product=");
  int loopv = 64;
  do
  {
    Serial.print(readBuff[loopv++]);
  }
  while ((readBuff[loopv] != 0) && (loopv < 128));
  Serial.println("");
}
