// ConfigEEPROM
// Routines which deal with Configuration EEPROM

#define MAGIC_NUM 0xaa          // Change to different number re-write default table

// Variable offsets in the EEPROM
#define FREQ0_OFFSET 0          // VFO 0 frequency (32-bits)
#define FREQ1_OFFSET 4
#define FREQ2_OFFSET 8
#define STEPSIZE_OFFSET 12      // Frequency step size (32-bits)
#define CALVAL_OFFSET 16        // Calibration factor in 1/100th of a Hz (32-bits)
#define VFO0ONOFF_OFFSET 20     // VFO 0 On/Off control
#define VFO1ONOFF_OFFSET 21
#define VFO2ONOFF_OFFSET 22
#define VFO0_1X4X_OFFSET 23       // VFO0 1x or 4x clock mult
#define VFO1_1X4X_OFFSET 24
#define VFO2_1X4X_OFFSET 25
#define VFONUMBER_OFFSET 26     // Current VFO number being set (0-2)
#define BAND_OFFSET 27          // Band number
#define MAGICNUMBER_OFFSET 28   // Reload defaults flag

// Load the configuration from the EEPROM
void loadEEPROM(void)
{
  VFO_0_Freq = EEPROM.get(FREQ0_OFFSET, VFO_0_Freq);
  VFO_1_Freq = EEPROM.get(FREQ1_OFFSET, VFO_1_Freq);
  VFO_2_Freq = EEPROM.get(FREQ2_OFFSET, VFO_2_Freq);
  stepSize = EEPROM.get(STEPSIZE_OFFSET, stepSize);
  calFactor = EEPROM.get(CALVAL_OFFSET, calFactor);
  VFO_0_OnOff = EEPROM.get(VFO0ONOFF_OFFSET, VFO_0_OnOff);
  VFO_1_OnOff = EEPROM.get(VFO1ONOFF_OFFSET, VFO_1_OnOff);
  VFO_2_OnOff = EEPROM.get(VFO2ONOFF_OFFSET, VFO_2_OnOff);
  VFO_0_1x4x = EEPROM.get(VFO0_1X4X_OFFSET, VFO_0_1x4x);
  VFO_1_1x4x = EEPROM.get(VFO1_1X4X_OFFSET, VFO_1_1x4x);
  VFO_2_1x4x = EEPROM.get(VFO2_1X4X_OFFSET, VFO_2_1x4x);
  bandNumber = EEPROM.get(BAND_OFFSET,bandNumber);
  currentVFONumber = EEPROM.get(VFONUMBER_OFFSET, currentVFONumber);
}

// Store the configuration to the EEPROM
void storeEEPROM(void)
{
  uint8_t magicNumber = MAGIC_NUM;
  EEPROM.put(FREQ0_OFFSET, VFO_0_Freq);
  EEPROM.put(FREQ1_OFFSET, VFO_1_Freq);
  EEPROM.put(FREQ2_OFFSET, VFO_2_Freq);
  EEPROM.put(STEPSIZE_OFFSET, stepSize);
  EEPROM.put(CALVAL_OFFSET, calFactor);
  EEPROM.put(VFO0ONOFF_OFFSET, VFO_0_OnOff);
  EEPROM.put(VFO1ONOFF_OFFSET, VFO_1_OnOff);
  EEPROM.put(VFO2ONOFF_OFFSET, VFO_2_OnOff);
  EEPROM.put(VFO0_1X4X_OFFSET, VFO_0_1x4x);
  EEPROM.put(VFO1_1X4X_OFFSET, VFO_1_1x4x);
  EEPROM.put(VFO2_1X4X_OFFSET, VFO_2_1x4x);
  EEPROM.put(VFONUMBER_OFFSET, currentVFONumber);
  EEPROM.put(BAND_OFFSET,bandNumber);
  EEPROM.put(MAGICNUMBER_OFFSET, magicNumber);
}

// Set default EEPROM values
// Loaded only the first time the program is run on a "virgin" Arduino Pro Mini
void setEEPROMDefaults(void)
{
  VFO_0_Freq = 1415000000ULL;
  VFO_1_Freq = 1200000000ULL;
  VFO_2_Freq = 1000000000ULL;
  stepSize = STEP_1_MHZ;
  calFactor = 0;
  VFO_0_OnOff = VFO_ON;
  VFO_1_OnOff = VFO_OFF;
  VFO_2_OnOff = VFO_OFF;
  VFO_0_1x4x = VFO_1X;
  VFO_1_1x4x = VFO_1X;
  VFO_2_1x4x = VFO_1X;
  bandNumber = BAND_20M_SSB;
  currentVFONumber = 0;
}

// If the magic number is present, then load the default values from thr EEPROM
// If the magic number is not present, then store the default values to the EEPROM
void loadInitEEPROM(void)
{
  magicNumber = MAGIC_NUM;
#ifdef HAS_INTERNAL_EEPROM
  if (EEPROM.get(MAGICNUMBER_OFFSET, magicNumber) == MAGIC_NUM)
    loadEEPROM();
  else
  {
    setEEPROMDefaults();
    storeEEPROM();
  }
#endif
}

void loadMemory(uint8_t memNum)
{
  VFO_0_Freq =        EEPROM.get(32 + ((memNum << 5) + FREQ0_OFFSET),     VFO_0_Freq);
  VFO_1_Freq =        EEPROM.get(32 + ((memNum << 5) + FREQ1_OFFSET),     VFO_1_Freq);
  VFO_2_Freq =        EEPROM.get(32 + ((memNum << 5) + FREQ2_OFFSET),     VFO_2_Freq);
  stepSize =          EEPROM.get(32 + ((memNum << 5) + STEPSIZE_OFFSET),  stepSize);
  calFactor =         EEPROM.get(32 + ((memNum << 5) + CALVAL_OFFSET),    calFactor);
  VFO_0_OnOff =       EEPROM.get(32 + ((memNum << 5) + VFO0ONOFF_OFFSET), VFO_0_OnOff);
  VFO_1_OnOff =       EEPROM.get(32 + ((memNum << 5) + VFO1ONOFF_OFFSET), VFO_1_OnOff);
  VFO_2_OnOff =       EEPROM.get(32 + ((memNum << 5) + VFO2ONOFF_OFFSET), VFO_2_OnOff);
  VFO_0_1x4x =        EEPROM.get(32 + ((memNum << 5) + VFO0_1X4X_OFFSET), VFO_0_1x4x);
  VFO_1_1x4x =        EEPROM.get(32 + ((memNum << 5) + VFO1_1X4X_OFFSET), VFO_1_1x4x);
  VFO_2_1x4x =        EEPROM.get(32 + ((memNum << 5) + VFO2_1X4X_OFFSET), VFO_2_1x4x);
  currentVFONumber =  EEPROM.get(32 + ((memNum << 5) + VFONUMBER_OFFSET), currentVFONumber);
  bandNumber =        EEPROM.get(32 + ((memNum << 5) + BAND_OFFSET),      bandNumber);
  setupVFO();
}

void storeMemory(uint8_t memNum)
{
  EEPROM.put(32 + ((memNum << 5) + FREQ0_OFFSET),     VFO_0_Freq);
  EEPROM.put(32 + ((memNum << 5) + FREQ1_OFFSET),     VFO_1_Freq);
  EEPROM.put(32 + ((memNum << 5) + FREQ2_OFFSET),     VFO_2_Freq);
  EEPROM.put(32 + ((memNum << 5) + STEPSIZE_OFFSET),  stepSize);
  EEPROM.put(32 + ((memNum << 5) + CALVAL_OFFSET),    calFactor);
  EEPROM.put(32 + ((memNum << 5) + VFO0ONOFF_OFFSET), VFO_0_OnOff);
  EEPROM.put(32 + ((memNum << 5) + VFO1ONOFF_OFFSET), VFO_1_OnOff);
  EEPROM.put(32 + ((memNum << 5) + VFO2ONOFF_OFFSET), VFO_2_OnOff);
  EEPROM.put(32 + ((memNum << 5) + VFO0_1X4X_OFFSET), VFO_0_1x4x);
  EEPROM.put(32 + ((memNum << 5) + VFO1_1X4X_OFFSET), VFO_1_1x4x);
  EEPROM.put(32 + ((memNum << 5) + VFO2_1X4X_OFFSET), VFO_2_1x4x);
  EEPROM.put(32 + ((memNum << 5) + VFONUMBER_OFFSET), currentVFONumber);
  EEPROM.put(32 + ((memNum << 5) + BAND_OFFSET),      bandNumber);
}
