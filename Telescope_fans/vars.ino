//------------------------------------------------------------------------------------------
// Utilitary functions and global variables
//------------------------------------------------------------------------------------------
CState    state;
CSettings settings;
//------------------------------------------------------------------------------------------
#ifdef DEBUG
char    text[128];
#else
char    text[32];
#endif
//------------------------------------------------------------------------------------------
#define RESISTOR_TO_PWR     46.9f // 44.3f // power voltage measurement divider R1, kOhms
#define RESISTOR_TO_GND     20.1f // 17.9f // power voltage measurement divider R2, kOhms
#define POWER_LOSS_CUTOFF   10.0f // voltage drop on +12V power source which is considered as power loss
#define ADC_TO_VOLTS        (5.0f / 1023.0f * (RESISTOR_TO_PWR + RESISTOR_TO_GND) / RESISTOR_TO_GND)
//------------------------------------------------------------------------------------------
CVariable * CVariable::First  = NULL;
CVariable * CVariable::Cur    = NULL;
//------------------------------------------------------------------------------------------
//                                 def,        min,       max, step, div,    unit, special,   special text
CVariable varComboInfoMode (         0,          0, D_COUNT-1,    1,   1,      "",  V_LOOP,             "");    // combo display mode
CVariable varCoolingMode   (         0,          0, C_COUNT-1,    1,   1,      "",  V_LOOP,             "");    // cooling mode
CVariable varTargetDeltaT  (         5,          0,        50,    1,  10, DEG "C",       0, "0.05" DEG "C");    // in millidegrees (divider = 10, value = 0 for 0.05°C)
CVariable varCoolingSpeed  (       100,         10,       100,    5,   1,     "%",  V_NONE,             "");    // cooling fan speed duty
CVariable varKeepingSpeed  (        20,          0,       100,    5,   1,     "%",  V_NONE,             "");    // keeping temperature fan speed duty
CVariable varDisplayBright (         1,          1,        10,    1,   1,      "",  V_NONE,             "");    // display drightness
CVariable varDisplayContr  (         1,          1,        10,    1,   1,      "",  V_NONE,             "");    // display contrast
CVariable varDisplayTimeout(        30,          0,       120,    5,   1,  " sec",       0,     "Disabled");    // display off timeout in seconds (0 for disabled)
CVariable varFanStuckAlarm (         1,          0,         1,    1,   1,      "",  V_BOOL,             "");    // fan stuck alarm on/off; # means values are displayed as "on/off"
CVariable varDtSecondSensor( S_AMBIENT, S_MIRROR+1, S_COUNT-1,    1,   1,      "",  V_LOOP,             "");    // second sensor (in pair to S_MIRROR) used to calculate target dT
CVariable varSensor0Index  (         0,          0, S_COUNT-1,    0,   0,      "",  V_ADDR,             "");
CVariable varSensor1Index  (         0,          0, S_COUNT-1,    0,   0,      "",  V_ADDR,             "");
CVariable varSensor2Index  (         0,          0, S_COUNT-1,    0,   0,      "",  V_ADDR,             "");
CVariable varSensor3Index  (         0,          0, S_COUNT-1,    0,   0,      "",  V_ADDR,             "");
//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------

CVariable::CVariable(int16_t v, int16_t vmin, int16_t vmax, int16_t vstep,
                     int16_t vdiv, const char * txtun, int16_t vsp, const char * txtsp)
{
  valueSpecial = vsp;

  if (valueSpecial == V_ADDR)
    reset();
  else
  {
    valueDef = value = v;
    valueMin = vmin;
    valueMax = vmax;
    valueStep = vstep;
    valueDivider = vdiv;
    textSpecial  = txtsp;
    textUnit = txtun;
    clamp();
  }

  // init list
  Next = nullptr;
  if (First == NULL)
    First = this;
  else
    Cur->Next = this;
  Cur = this;
}

//------------------------------------------------------------------------------------------

void  CVariable::reset()
{
  if (valueSpecial == V_ADDR)
    memset(address, 0xff, sizeof(address));
  else
    value = valueDef;
}

//------------------------------------------------------------------------------------------

bool  CVariable::set(int16_t v)
{
  value = v;
  return clamp();
}

//------------------------------------------------------------------------------------------

float CVariable::getf()
{
  if (valueDivider == 1)
    return (float)value;
  else
    return (float)value / (float)valueDivider;
}

//------------------------------------------------------------------------------------------

void  CVariable::inc()
{
  switch (valueSpecial)
  {
    case V_BOOL: // bool variable
      value = 1 - value;
      break;

    case V_LOOP: // looped increment
      value += valueStep;
      if (value > valueMax)
          value = valueMin;
      break;

    case V_ADDR:
      temp.GetNextAddress(address);
      break;

    default: // clamped increment
      value += valueStep;
      clamp();
      break;
  }
}

//------------------------------------------------------------------------------------------

void  CVariable::dec()
{
  switch (valueSpecial)
  {
    case V_BOOL: // bool variable
      value = 1 - value;
      break;

    case V_LOOP: // looped decrement
      value -= valueStep;
      if (value < valueMin)
          value = valueMax;
      break;

    case V_ADDR:
      temp.GetPrevAddress(address);
      break;

    default:
      value -= valueStep;
      clamp();
      break;
  }
}

//------------------------------------------------------------------------------------------

bool  CVariable::isValueSpecial()
{
  return (textSpecial != NULL) && (value == valueSpecial);
}

//------------------------------------------------------------------------------------------

const char * CVariable::getValueStr()
{
  if (isValueAddress())
  {
    if (temp.isAddressValid(address))
    {
      AddressToHexStr(address, text);
      return text;
    }
    else
      return LoadMessage(TXT_NOT_ASSIGNED);
  }
  else if (isValueSpecial())
    return textSpecial;
  else if (valueSpecial == V_BOOL)
  {
    return (value == 1) ? "On" : "Off";
  }
  else
  {
    if (valueDivider == 1)
      sprintf(text, "%i%s", value, textUnit);
    else
      sprintf(text, "%i.%01i%s", value / valueDivider, value % valueDivider, textUnit);
    return text;
  }
}

//------------------------------------------------------------------------------------------

bool CVariable::clamp()
{
  if (value < valueMin) { value = valueMin; return false; }
  if (value > valueMax) { value = valueMax; return false; }
  return true;
}

//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------
// Reads variables from EEPROM

void    CSettings::Init()
{
  pinMode(POWER_DETECT_PIN, INPUT);

#ifdef DEBUG
  Serial.println(F("Loading variables..."));
  char text2[128];
#endif

  int16_t v = 0;
  int  addr = 0;

  for (CVariable * var = CVariable::First; var != NULL; var = var->Next)
  {
    if (var->isValueAddress())
    {
      EEPROM.get(addr, var->address);
      addr += sizeof(var->address);

      #ifdef DEBUG
        sprintf(text, "addr = %i, EEPROM = ", addr);
        Serial.print(text);
        AddressToHexStr(var->address, text);
        Serial.println(text);
      #endif
    }
    else
    {
      EEPROM.get(addr, v);
      addr += sizeof(int16_t);
  
      // if value read from EEPROM is out of range, this is probably first run,
      // we must reset variable to default.
      if (!var->set(v))
        var->reset();
  
      #ifdef DEBUG
        sprintf(text2, "addr = %i, EEPROM = %i, var = %i", addr, v, var->value);
        Serial.println(text2);
      #endif
    }
  }
}

//------------------------------------------------------------------------------------------
// Writes variables to EEPROM

void    CSettings::Write()
{
#ifdef DEBUG
  Serial.println(F("Saving variables..."));
#endif

  int  addr = 0;

  for (CVariable * var = CVariable::First; var != NULL; var = var->Next)
  {
    if (var->isValueAddress())
    {
      EEPROM.put(addr, var->address);
      addr += sizeof(var->address);

      #ifdef DEBUG
        sprintf(text, "addr = %i, var = ", addr);
        Serial.print(text);
        AddressToHexStr(var->address, text);
        Serial.println(text);
      #endif
    }
    else
    {
      EEPROM.put(addr, var->value);
      addr += sizeof(var->value);
  
      #ifdef DEBUG
        sprintf(text, "addr = %i, var = %i", addr, var->value);
        Serial.println(text);
      #endif
    }
  }
}

//------------------------------------------------------------------------------------------
// Resets variables to defaults

void    CSettings::Reset()
{
#ifdef DEBUG
  Serial.println(F("Resetting variables..."));
#endif

  for (CVariable * var = CVariable::First; var != NULL; var = var->Next)
  {
    var->reset();

#ifdef DEBUG
    Serial.println(var->value);
#endif
  }
}

//------------------------------------------------------------------------------------------
// Writes variables to EEPROM if minimal time after last saving has passed

void    CSettings::Save()
{
  uint32_t t = millis();
  uint32_t timePassed = t - lastSaveTime;

  if (firstPowerLoss || (timePassed > EEPROM_WRITE_WAIT_TIME))
  {
#ifdef DEBUG
      Serial.print(F("!!!! Power lost, saving variables !!!! V = "));
      Serial.println(voltage);
#endif
  
    Write();
    lastSaveTime = t;

    // Wait until last data chunck recorded to EEPROM
    delay(POWER_DETECT_PERIOD);

    // Indicate that data has been saved sucessfully with onboard LED
    digitalWrite(BOARD_LED_PIN, HIGH);
  }

  firstPowerLoss = false;
}

//------------------------------------------------------------------------------------------
// Returns true if power loss detected

bool    CSettings::DetectPowerLoss()
{
  // Measure 12V line voltage, convert to volts
  int v = analogRead(POWER_DETECT_PIN);
  voltage = (float)v * ADC_TO_VOLTS;

  voltageSum += voltage;

  // Detect power loss as a dropping of 12V line voltage.
  // If voltage is < 5V, we are powering from USB, so don't
  // detect this as a power loss (USB debug mode).
  poweredByUSB = (voltage < 6.0f);
  powerLostPrev = powerLost;
  powerLost = !poweredByUSB && (voltage < POWER_LOSS_CUTOFF);

  return powerLost;
}

//------------------------------------------------------------------------------------------

void    CSettings::Update(int NumCycles)
{
  voltageAvg = voltageSum / NumCycles;
  voltageSum = 0.0f;

  // Switch off onboard LED if it was turned on
  if (digitalRead(BOARD_LED_PIN) == HIGH)
    digitalWrite(BOARD_LED_PIN, LOW);
}

//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------

const char * GetCoolingModeStr()
{
  switch (varCoolingMode.value)
  {
    case C_COOL_AND_KEEP: return LoadMessage(TXT_KEEP_DT);
    case C_COOL_AND_BLOW: return LoadMessage(TXT_KEEP_BLOWING);
    case C_COOL_AND_SUCK: return LoadMessage(TXT_KEEP_DRAWING);
    case C_COOL_AND_OFF:  return LoadMessage(TXT_STOP);
    default:              return LoadMessage(TXT_COOLING_OFF);
  }
}

//------------------------------------------------------------------------------------------

const char * GetSensorPairStr()
{
  switch (varDtSecondSensor.value)
  {
    case S_TUBE:     return LoadMessage(TXT_MIRR_AND_TUBE);
    case S_AMBIENT:  return LoadMessage(TXT_MIRR_AND_AMB);
    case S_EXTERNAL: return LoadMessage(TXT_MIRR_AND_EXT);
    default:         return LoadMessage(TXT_ERROR);
  }  
}

//------------------------------------------------------------------------------------------

const char * GetTimeStr()
{
  uint32_t ms  = millis();
  uint32_t s = ms / 1000;
  uint32_t m = s  / 60;
  uint32_t h = m  / 60;
  uint32_t d = h  / 24;
  s = s % 60;
  m = m % 60;
  h = h % 24;
  
  sprintf(text, "%lud %02lu:%02lu:%02lu", d, h, m, s);
  return text;
}

//------------------------------------------------------------------------------------------

const char * GetVoltageStr()
{
  sprintf(text, "%4.2f V", settings.GetVoltage());
  return text;
}

//------------------------------------------------------------------------------------------

const char * GetAboutStr()
{
  return LoadMessage(TXT_COPYRIGHT);
}

//------------------------------------------------------------------------------------------




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

void  CState::PrintFanRPMHelper(const char * symbol, int pos, uint32_t RPM)
{
  char * buf = &text[pos];
  sprintf(buf, "%s%5lu", symbol, RPM);
}
//------------------------------------------------------------------------------------------

void  CState::PrintFanDutyHelper(const char * symbol, int pos, int duty)
{
  char * buf = &text[pos];
  if (duty == 0)
    sprintf(buf, "%s  off ", symbol);
  else
    sprintf(buf, "%s% 4i%%", symbol, duty);
}


//------------------------------------------------------------------------------------------

char * CState::GetTempStyle1Str0()
{
  if (varDtSecondSensor.value == S_EXTERNAL)
    PrintTempHelper(" E", 0, temp[S_EXTERNAL]);
  else
    PrintTempHelper(" A", 0, temp[S_AMBIENT]);

  PrintTempHelper(" M", 8, temp[S_MIRROR]);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempStyle1Str1()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintTempHelper(" T",      8, temp[S_TUBE]);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStyle1Str0()
{
  if (varDtSecondSensor.value == S_EXTERNAL)
    PrintTempHelper(" E", 0, temp[S_EXTERNAL]);
  else
    PrintTempHelper(" A", 0, temp[S_AMBIENT]);

  PrintFanDutyHelper("  F", 8, fanDuty1);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStyle1Str1()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintFanDutyHelper ("  R", 8, fanDuty2);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStyle2Str0()
{
  if (varDtSecondSensor.value == S_EXTERNAL)
    PrintTempHelper(" E", 0, temp[S_EXTERNAL]);
  else
    PrintTempHelper(" A", 0, temp[S_AMBIENT]);

  PrintFanRPMHelper("  F", 8, fanRPM1);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetTempFansStyle2Str1()
{
  PrintTempHelper(DELTA "T", 0, tempDelta);
  PrintFanRPMHelper  ("  R", 8, fanRPM2);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetFansStr0()
{
  PrintFanDutyHelper("Front", 0, fanDuty1);
  PrintFanRPMHelper (" ",    10, fanRPM1);
  return text;
}

//------------------------------------------------------------------------------------------

char * CState::GetFansStr1()
{
  PrintFanDutyHelper(" Rear", 0, fanDuty2);
  PrintFanRPMHelper (" ",    10, fanRPM2);
  return text;
}

//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------

void  AddressToHexStr(byte * a, char * buf)
{
  const char hex[17] = "0123456789ABCDEF";
  int c = 0;
  for (int i=0; i<8; ++i)
  {
    buf[c++] = hex[a[i] >> 4];
    buf[c++] = hex[a[i] & 0x0F];
  }
  buf[c++] = 0;
}

//------------------------------------------------------------------------------------------
