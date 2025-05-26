//------------------------------------------------------------------------------------------
// Utilitary functions and global variables
//------------------------------------------------------------------------------------------
#ifdef DEBUG
char    text[64];
#else
char    text[32];
#endif
//------------------------------------------------------------------------------------------
CVariable * CVariable::First  = NULL;
CVariable * CVariable::Cur    = NULL;
//------------------------------------------------------------------------------------------
//                                 def,        min,       max, step, div,    unit, special,   special text
CVariable varComboInfoMode (         0,          0, D_COUNT-1,    1,   1,      "",  V_LOOP,             "");    // combo display mode
CVariable varCoolingMode   (         0,          0, C_COUNT-1,    1,   1,      "",  V_LOOP,             "");    // cooling mode
CVariable varCoolingEnabled(         1,          0,         1,    1,   1,      "",  V_BOOL,             "");    // cooling enabled
CVariable varTargetDeltaT  (         5,          0,        50,    1,  10, DEG "C",       0, "0.05" DEG "C");    // in millidegrees (divider = 10, special value = 0 for 0.05°C)
CVariable varCoolingSpeed  (       100,         10,       100,    5,   1,     "%",  V_NONE,             "");    // cooling fan speed duty
CVariable varKeepingSpeed  (        20,          0,       100,    5,   1,     "%",  V_NONE,             "");    // keeping temperature fan speed duty
CVariable varPosPressure   (        50,          0,       100,    5,   1,     "%",  V_NONE,             "");    // intake vs exhaust fan speed duty
CVariable varDisplayBright (         1,          1,        10,    1,   1,      "",  V_NONE,             "");    // display drightness
CVariable varDisplayContr  (         1,          1,        10,    1,   1,      "",  V_NONE,             "");    // display contrast
CVariable varDisplayTimeout(        30,          0,       120,    5,   1,  " sec",       0,            "-");    // display off timeout in seconds (0 for disabled)
CVariable varFanStuckAlarm (         1,          0,         1,    1,   1,      "",  V_BOOL,             "");    // fan stuck alarm on/off
CVariable varLowBattAlarm  (         1,          0,         1,    1,   1,      "",  V_BOOL,             "");    // low battery alarm on/off
CVariable varBattAlarmVolt (       100,         80,       120,    1,  10,    " V",  V_NONE,             "");    // low battery alarm threshold (divider = 10)
CVariable varDtSecondSensor( S_AMBIENT, S_MIRROR+1, S_COUNT-1,    1,   1,      "",  V_LOOP,             "");    // second sensor (in pair to S_MIRROR) used to calculate target dT
CVariable varSensor0Index  (         0,          0,         0,    0,   0,      "",  V_ADDR,             "");
CVariable varSensor1Index  (         0,          0,         0,    0,   0,      "",  V_ADDR,             "");
CVariable varSensor2Index  (         0,          0,         0,    0,   0,      "",  V_ADDR,             "");
CVariable varSensor3Index  (         0,          0,         0,    0,   0,      "",  V_ADDR,             "");
#ifdef BI_LANG
CVariable varDisplayLang   (         0,          0,         1,    1,   1,      "",  V_BOOL,             "");    // language
#endif
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

float CVariable::getMinf()
{
  if (valueDivider == 1)
    return (float)valueMin;
  else
    return (float)valueMin / (float)valueDivider;
}

//------------------------------------------------------------------------------------------

float CVariable::getMaxf()
{
  if (valueDivider == 1)
    return (float)valueMax;
  else
    return (float)valueMax / (float)valueDivider;
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
    return (value == 1) ? LoadMessage(TXT_ON) : LoadMessage(TXT_OFF);
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
