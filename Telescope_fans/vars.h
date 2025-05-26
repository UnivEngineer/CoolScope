#ifndef VARS_H
#define VARS_H
//------------------------------------------------------------------------------------------
// Utilitary functions and global variables
//------------------------------------------------------------------------------------------
#ifdef DEBUG
extern  char    text[64];
#else
extern  char    text[32];
#endif
//------------------------------------------------------------------------------------------

enum  ECoolingModes
{
  C_COOL_AND_KEEP = 0,  // cool down, then keep all   fans at minimal speed
  C_COOL_AND_BLOW,      // cool down, then keep front fans at minimal speed to blow out boundary layer
  C_COOL_AND_SUCK,      // cool down, then keep rear  fans at minimal speed
  C_COOL_AND_STOP,      // cool down, then stop
  C_COUNT
};

//------------------------------------------------------------------------------------------

enum  EDispModes
{
  D_TEMP_STYLE_1 = 0,
  D_COMBO_STYLE_1,
  D_COMBO_STYLE_2,
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
  float getMinf();
  float getMaxf();
  void  inc();
  void  dec();
  bool  isValueSpecial();
  bool  isValueAddress() { return valueSpecial == V_ADDR; }
  const char * getValueStr();
};

//------------------------------------------------------------------------------------------
extern  CVariable varComboInfoMode;
extern  CVariable varCoolingMode;
extern  CVariable varCoolingEnabled;
extern  CVariable varTargetDeltaT;
extern  CVariable varCoolingSpeed;
extern  CVariable varKeepingSpeed;
extern  CVariable varPosPressure;
extern  CVariable varDisplayBright;
extern  CVariable varDisplayContr;
extern  CVariable varDisplayTimeout;
extern  CVariable varFanStuckAlarm;
extern  CVariable varLowBattAlarm;
extern  CVariable varBattAlarmVolt;
extern  CVariable varDtSecondSensor;
extern  CVariable varSensor0Index;
extern  CVariable varSensor1Index;
extern  CVariable varSensor2Index;
extern  CVariable varSensor3Index;
#ifdef BI_LANG
extern  CVariable varDisplayLang;
#endif
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
