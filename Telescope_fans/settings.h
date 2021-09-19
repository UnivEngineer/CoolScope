#ifndef SETTINGS_H
#define SETTINGS_H
//------------------------------------------------------------------------------------------
// Save/load settings to EEPROM, power loss detection
//------------------------------------------------------------------------------------------
#include <EEPROM.h>
//------------------------------------------------------------------------------------------

class CSettings
{
  uint32_t  lastSaveTick      = 0;
  uint32_t  lastPowerLossTick = 0;
  bool      powerLost      = false;
  bool      powerLostPrev  = false;
  bool      firstPowerLoss = true;
  bool      poweredByUSB   = false;
  float     voltage        = 0.0f;
  float     voltageSum     = 0.0f;
  float     voltageAvg     = 0.0f;

  void      Write();

public:

  CSettings() {};
  
  void  Init();
  void  Reset();
  void  Save();
  void  Update(int NumCycles);
  bool  DetectPowerLoss();
  bool  isPowerLost()     { return powerLost; }
  bool  isPowerRestored() { return !powerLost && powerLostPrev; }
  bool  isPoweredByUSB()  { return poweredByUSB; }
  bool  isLowBattery();
  float GetVoltage()      { return voltageAvg; }
};

//------------------------------------------------------------------------------------------
extern  CSettings settings;
//------------------------------------------------------------------------------------------
#endif // SETTINGS_H
