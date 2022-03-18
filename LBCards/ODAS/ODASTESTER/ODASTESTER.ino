//////////////////////////////////////////////////////////
// ODASTESTER Factory Test code
// Test each card and channel
// Read/write EEPROM if there is one
//////////////////////////////////////////////////////////
// Tester Hardware
//  Blue Pill Hub card
//    http://land-boards.com/blwiki/index.php?title=Blue_Pill_Hub
//  DIGIO32-I2C 32 bit I2C card
//    http://land-boards.com/blwiki/index.php?title=DIGIO32-I2C
//  LED-32 card
//    http://land-boards.com/blwiki/index.php?title=LED-32
//////////////////////////////////////////////////////////

#include <LandBoards_DIGIO32I2C.h>
#include <LandBoards_Digio128V2.h>
#include <LandBoards_Digio128_64.h>
#include <LandBoards_I2CIO8.h>
#include <LandBoards_I2CIO8X.h>
#include <LandBoards_I2CTEMP01.h>
#include <LandBoards_I2CRPT01.h>
#include <LandBoards_I2CRPT08.h>
#include <LandBoards_MCP23017.h>
#include <LandBoards_MCP23008.h>

//////////////////////////////////////////////////////////
// defines follow

#define SERIAL_DEBUG Serial

typedef enum {
  NONE,
  DIGIO16I2C_CARD = 1,
  DIGIO128_CARD,
  DIGIO128_64_CARD,
  OPTOIN8I2C_CARD,
  OPTOOUT8I2C_CARD,
  DIGIO32I2C_CARD,
  PROTO16I2C_CARD,
  ODASPSOC5_CARD,
  ODASRELAY16_CARD,
  NEW_CARD = 499,
  NOEEPROMAFTER = 500,
  I2CIO8_CARD,
  I2CIO8X_CARD,
  OPTOFST_SML_NON_INVERTING_CARD,
  OPTOFST_SML_INVERTING_CARD,
  OPTOFSTBI_CARD,
  I2CRPT01_CARD,
  I2CRPT08_CARD,
  SWLEDX8_I2C_CARD,
  UNKNOWN_BOARD,
} boardType_t;

enum {TEST_PASSED, TEST_FAILED};

//////////////////////////////////////////////////////////
// globals follow

boardType_t boardType;

uint32_t failCount;
uint32_t passCount;
uint8_t single0loop1;

typedef enum {
  UUT_CARD_MUX_CH = 0x04,
  TEST_STN_INT_MUX_CH = 0x07,
  NO_MUX_CH = 0x00,
} muxChannel_t;

LandBoards_I2CRPT01 ODASTSTR_I2CMux;
LandBoards_Digio128V2 Dio128;    // Call the class constructor for the DigIO32_I2C card
LandBoards_Digio128_64 Dio128_64;    // Call the class constructor for the DigIO-128 card
LandBoards_DIGIO32I2C Dio32;
LandBoards_I2CIO8 i2cio8Card;
LandBoards_I2CIO8 i2cio8Card1;
LandBoards_I2CIO8 i2cio8Card2;
LandBoards_I2CIO8 i2cio8Card3;
LandBoards_I2CIO8 i2cio8Card4;
LandBoards_I2CIO8 i2cio8Card5;
LandBoards_I2CIO8 i2cio8Card6;
LandBoards_I2CIO8 i2cio8Card7;
LandBoards_I2CIO8 i2cio8Card8;
LandBoards_I2CIO8X i2cio8xCard;
LandBoards_MCP23008 singleMCP23008;
LandBoards_MCP23017 singleMCP23017;
LandBoards_I2CRPT01 UUTI2CMux;
LandBoards_I2CRPT08 UUTI2CMux8;

//////////////////////////////////////////////////////////
// setup()
//////////////////////////////////////////////////////////

void setup()
{
  // Set USB-Serial port to 9600 baud
  Serial.begin(9600);
  
  // Initialize the internal DIGIO32-I2C card
  ODASTSTR_I2CMux.begin(1);
  ODASTSTR_I2CMux.setI2CChannel(TEST_STN_INT_MUX_CH);
  Dio32.begin(0);
  ODASTSTR_I2CMux.setI2CChannel(NO_MUX_CH);

  // Global vars
  failCount = 0;
  passCount = 0;
  single0loop1 = 0;
  boardType = NEW_CARD;
  
  // If the UUT EEPROM was already set yp, use the information to setup card
  if (detectBoardInEeprom() == 1)
  {
    selectBoardType();
    eepromWrite();
  }
  ODASTSTR_I2CMux.setI2CChannel(UUT_CARD_MUX_CH);
  switch (boardType)    // Instantiate the classes here for the boards
  {
    case PROTO16I2C_CARD:
    case ODASRELAY16_CARD:
    case SWLEDX8_I2C_CARD:
      singleMCP23017.begin(0);
      break;
    case OPTOIN8I2C_CARD:
    case OPTOOUT8I2C_CARD:
      singleMCP23008.begin();               // use default address 0
      break;
    case DIGIO128_CARD:
      Dio128.begin();
      break;
    case DIGIO128_64_CARD:
      Dio128_64.begin();
      break;
    case DIGIO32I2C_CARD:
      Dio32.begin(0);
      break;
    case I2CIO8_CARD:
      i2cio8Card.begin();
      break;
    case I2CIO8X_CARD:
      i2cio8xCard.begin();
      break;
    case I2CRPT01_CARD:
      UUTI2CMux.begin(0);                   // testing external I2C-RPT-01 card
      UUTI2CMux.setI2CChannel(0); 
      i2cio8Card1.begin(0);                  // Requires I2CIO8 cards connected to external I2C-RPT-01 card
      UUTI2CMux.setI2CChannel(1); 
      i2cio8Card2.begin(0);
      UUTI2CMux.setI2CChannel(2); 
      i2cio8Card3.begin(0);
      UUTI2CMux.setI2CChannel(3); 
      i2cio8Card4.begin(0);
      break;
    case I2CRPT08_CARD:
      UUTI2CMux8.begin(0);                   // testing external I2C-RPT-01 card
      UUTI2CMux8.setI2CChannel(0,1); 
      i2cio8Card1.begin(0);                  // Requires I2CIO8 cards connected to external I2C-RPT-01 card
      UUTI2CMux8.setI2CChannel(0,0);
      UUTI2CMux8.setI2CChannel(1,1); 
      i2cio8Card2.begin(0);
      UUTI2CMux8.setI2CChannel(1,0);
      UUTI2CMux8.setI2CChannel(2,1); 
      i2cio8Card3.begin(0);
      UUTI2CMux8.setI2CChannel(2,0);
      UUTI2CMux8.setI2CChannel(3,1); 
      i2cio8Card4.begin(0);
      UUTI2CMux8.setI2CChannel(3,0);
      UUTI2CMux8.setI2CChannel(4,1); 
      i2cio8Card5.begin(0);
      UUTI2CMux8.setI2CChannel(4,0);
      UUTI2CMux8.setI2CChannel(5,1); 
      i2cio8Card6.begin(0);
      UUTI2CMux8.setI2CChannel(5,0);
      UUTI2CMux8.setI2CChannel(6,1); 
      i2cio8Card7.begin(0);
      UUTI2CMux8.setI2CChannel(6,0);
      UUTI2CMux8.setI2CChannel(7,1); 
      i2cio8Card8.begin(0);
      UUTI2CMux8.setI2CChannel(7,0);
      break;
  }
  Serial.println(F("C=Card Tests, D=Direct, E=EEPROM, I=access Internal DIGIO32"));
}

//////////////////////////////////////////////////////////
// loop()
//////////////////////////////////////////////////////////

void loop()
{
  while (1)
  {
    topLevelMenu();
  }
}
