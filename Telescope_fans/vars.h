#ifndef VARS_H
#define VARS_H
//------------------------------------------------------------------------------------------
// Utilitary functions and global variables
//------------------------------------------------------------------------------------------
#include <EEPROM.h>
//------------------------------------------------------------------------------------------
#ifdef DEBUG
extern  char    text[128];
#else
extern  char    text[32];
#endif
//------------------------------------------------------------------------------------------

enum  ECoolingModes
{
  C_COOL_AND_KEEP = 0,  // cool down, then keep all   fans at minimal speed
  C_COOL_AND_BLOW,      // cool down, then keep front fans at minimal speed to blow out boundary layer
  C_COOL_AND_SUCK,      // cool down, then keep rear  fans at minimal speed
  C_COOL_AND_OFF,       // cool down, then switch off
  C_OFF,                // cooling is off
  C_COUNT
};

//------------------------------------------------------------------------------------------

enum  EDispModes
{
  D_TEMP_STYLE_1 = 0,
  D_TEMP_FANS_STYLE_1,
  D_TEMP_FANS_STYLE_2,
  D_FANS,
  D_COUNT
};

//------------------------------------------------------------------------------------------
#define V_NONE   -1 // no special value for variable
#define V_LOOP   -2 // no special value for variable, looped incrementing/decrementing
#define V_BOOL   -3 // no special value for variable, boolean variable
#define V_ADDR   -4 // variable typr is address
//------------------------------------------------------------------------------------------

class   CState
{
public:

  float temp[S_COUNT];
  float tempDelta = 0.0f;

#ifdef USE_DHT
  float tempBoard = 0.0f;
  float humidity  = 0.0f;
#endif

  uint32_t fanRPM1 = 0;
  uint32_t fanRPM2 = 0;

  uint8_t  fanDuty1 = 0; // in %
  uint8_t  fanDuty2 = 0; // in %

  CState() {};

  char * GetTempStyle1Str0();
  char * GetTempStyle1Str1();
  char * GetTempFansStyle1Str0();
  char * GetTempFansStyle1Str1();
  char * GetTempFansStyle2Str0();
  char * GetTempFansStyle2Str1();
  char * GetFansStr0();
  char * GetFansStr1();

private:

  void  PrintTempHelper   (const char * symbol, int pos, float    T);
  void  PrintFanRPMHelper (const char * symbol, int pos, uint32_t RPM);
  void  PrintFanDutyHelper(const char * symbol, int pos, int      duty);
};

//------------------------------------------------------------------------------------------
const char * GetCoolingModeStr();
const char * GetTimeStr();
const char * GetVoltageStr();
const char * GetAboutStr();
const char * GetSensorPairStr();
//------------------------------------------------------------------------------------------
extern  CState  state;
//------------------------------------------------------------------------------------------

class  CVariable
{
public:

  int16_t value;
  int16_t valueSpecial;

  union
  {
    struct
    {
      int16_t valueMin;
      int16_t valueMax;
      int16_t valueDef;
      int16_t valueStep;
      int16_t valueDivider;
    };

    struct
    {
      byte  address[8];
      byte  reserved[2];
    };
  };

  static  CVariable * First;
  static  CVariable * Cur;
          CVariable * Next;

private:

  const char * textSpecial;
  const char * textUnit;

  bool  clamp();

public:

  CVariable(int16_t v, int16_t vmin, int16_t vmax, int16_t vstep,
            int16_t vdiv, const char * txtun, int16_t vsp, const char * txtsp);

  void  reset();
  bool  set(int16_t v);
  float getf();
  void  inc();
  void  dec();
  bool  isValueSpecial();
  bool  isValueAddress() { return valueSpecial == V_ADDR; }
  const char * getValueStr();
};

//------------------------------------------------------------------------------------------

class CSettings
{
  uint32_t  lastSaveTime   = 0;
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
  float GetVoltage()      { return voltageAvg; }
};

//------------------------------------------------------------------------------------------
extern  CVariable varComboInfoMode;
extern  CVariable varCoolingMode;
extern  CVariable varTargetDeltaT;
extern  CVariable varCoolingSpeed;
extern  CVariable varKeepingSpeed;
extern  CVariable varDisplayBright;
extern  CVariable varDisplayContr;
extern  CVariable varDisplayTimeout;
extern  CVariable varFanStuckAlarm;
extern  CVariable varDtSecondSensor;
extern  CVariable varSensor0Index;
extern  CVariable varSensor1Index;
extern  CVariable varSensor2Index;
extern  CVariable varSensor3Index;
//------------------------------------------------------------------------------------------
extern  CSettings settings;
//------------------------------------------------------------------------------------------
int   clampi(int   x, int   a, int   b) { return x<a ? a : (x>b ? b : x); }
float clampf(float x, float a, float b) { return x<a ? a : (x>b ? b : x); }
int   saturatei(int   x) { return x<0 ? 0 : (x>1 ? 1 : x); }
float saturatef(float x) { return x<0 ? 0 : (x>1 ? 1 : x); }
int   mixi(int   a, int   b, int   t) { return a + (b - a) * t / 100; }
float mixf(float a, float b, float t) { return a + (b - a) * t; }
//------------------------------------------------------------------------------------------
void  AddressToHexStr(byte * a, char * buf);
//------------------------------------------------------------------------------------------
#endif // VARS_H
