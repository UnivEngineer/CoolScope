//------------------------------------------------------------------------------------------
// State variables
//------------------------------------------------------------------------------------------
CState    state;
//------------------------------------------------------------------------------------------

const char * CState::GetFanSymbol(int duty)
{
  if (duty == 0)
      return FAN3;
  else
  {
    int animSpeed = display.isOLED ? 250 : 500;
    int phase = (millis() / animSpeed) % 3;
    switch (phase)
    {
      case 0:  return FAN1;
      case 1:  return FAN2;
      default: return FAN3;
    }
  }
}

//------------------------------------------------------------------------------------------

void  CState::PrintTempHelper(const char * symbol, int pos, float T)
{
  char * buf = &text[pos];
  if (T < -300.0f)
    sprintf(buf, "%s ---- ", symbol);
  else
    sprintf(buf, "%s% 5.1f" DEG, symbol, T);
}

//------------------------------------------------------------------------------------------

void  CState::PrintFanRPMHelper(const char * symbol, int pos, int duty, uint32_t RPM, bool fanSymbol)
{
  char * buf = &text[pos];
  sprintf(buf, "%s%s%5lu", symbol, fanSymbol ? GetFanSymbol(duty) : "", RPM);
}

//------------------------------------------------------------------------------------------

void  CState::PrintFanDutyHelper(const char * symbol, int pos, int duty, bool fanSymbol)
{
  char * buf = &text[pos];
  if (duty == 0)
    sprintf(buf, "%s%s off ", symbol, fanSymbol ? GetFanSymbol(duty) : "");
  else
    sprintf(buf, "%s%s% 4i%%", symbol, fanSymbol ? GetFanSymbol(duty) : "", duty);
}

//------------------------------------------------------------------------------------------

void  CState::PrintVoltHelper(const char * symbol, int pos)
{
  char * buf = &text[pos];
  if (settings.isPoweredByUSB())
    sprintf(buf, "%s [USB] ", symbol);
  else
    sprintf(buf, "%s% 5.1fV", symbol, settings.GetVoltage());
}

//------------------------------------------------------------------------------------------

char * CState::GetTempStr0()
{
  if (varDtSecondSensor.value == S_EXTERNAL)
    PrintTempHelper(" E", 0, temp[S_EXTERNAL]);
  else
    PrintTempHelper(" A", 0, temp[S_AMBIENT]);

  PrintTempHelper(" M", 8, temp[S_MIRROR]);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempStr1()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintTempHelper(" T",      8, temp[S_TUBE]);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetComboStr0()
{
  if (varDtSecondSensor.value == S_EXTERNAL)
    PrintTempHelper(" E", 0, temp[S_EXTERNAL]);
  else
    PrintTempHelper(" A", 0, temp[S_AMBIENT]);

  PrintVoltHelper(" " BATT, 8);
  
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetComboStr1Style1()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintFanDutyHelper(" ", 8, max(fanDuty1, fanDuty2), true);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetComboStr1Style2()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintFanRPMHelper(" ", 8, max(fanDuty1, fanDuty2), max(fanRPM1, fanRPM2), true);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStr0Style1()
{
  if (varDtSecondSensor.value == S_EXTERNAL)
    PrintTempHelper(" E", 0, temp[S_EXTERNAL]);
  else
    PrintTempHelper(" A", 0, temp[S_AMBIENT]);

  PrintFanDutyHelper(" F", 8, fanDuty1, true);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStr1Style1()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintFanDutyHelper (" R", 8, fanDuty2, true);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStr0Style2()
{
  if (varDtSecondSensor.value == S_EXTERNAL)
    PrintTempHelper(" E", 0, temp[S_EXTERNAL]);
  else
    PrintTempHelper(" A", 0, temp[S_AMBIENT]);

  PrintFanRPMHelper(" F", 8, fanDuty1, fanRPM1, true);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStr1Style2()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintFanRPMHelper  (" R", 8, fanDuty2, fanRPM2, true);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetFansStr0()
{
  PrintFanDutyHelper("Front", 0, fanDuty1,          false);
  PrintFanRPMHelper (" ",    10, fanDuty1, fanRPM1, false);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetFansStr1()
{
  PrintFanDutyHelper(" Rear", 0, fanDuty2,          false);
  PrintFanRPMHelper (" ",    10, fanDuty2, fanRPM2, false);
  return text;
}

//------------------------------------------------------------------------------------------
