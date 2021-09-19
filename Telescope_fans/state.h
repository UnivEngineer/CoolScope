#ifndef STATE_H
#define STATE_H
//------------------------------------------------------------------------------------------
// State variables
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

  char * GetTempStr0();
  char * GetTempStr1();
  char * GetComboStr0();
  char * GetComboStr1Style1();
  char * GetComboStr1Style2();
  char * GetTempFansStr0Style1();
  char * GetTempFansStr1Style1();
  char * GetTempFansStr0Style2();
  char * GetTempFansStr1Style2();
  char * GetFansStr0();
  char * GetFansStr1();

private:

  const char * GetFanSymbol(int duty);
  void  PrintTempHelper   (const char * symbol, int pos, float T);
  void  PrintFanRPMHelper (const char * symbol, int pos, int duty, uint32_t RPM,  bool fanSymbol);
  void  PrintFanDutyHelper(const char * symbol, int pos, int duty,                bool fanSymbol);
  void  PrintVoltHelper   (const char * symbol, int pos);
};

//------------------------------------------------------------------------------------------
extern  CState  state;
//------------------------------------------------------------------------------------------
#endif // STATE_H
