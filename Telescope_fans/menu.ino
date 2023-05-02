//------------------------------------------------------------------------------------------
// menu
//------------------------------------------------------------------------------------------
#include "vars.h"
//------------------------------------------------------------------------------------------
CMenu menu;
//------------------------------------------------------------------------------------------

CMenuNode CMenu::node[] =
{
  // name,                parent,            next,               prev,              child,             var,                getStrFunc

  // Main menu

  { TXT_COOLING,          MENU_ROOT,         MENU_MAIN_SENSORS,  MENU_MAIN_INFO,    MENU_COOL_ENABLED, NULL,               NULL },
  { TXT_SENSORS,          MENU_ROOT,         MENU_MAIN_DISPLAY,  MENU_MAIN_COOLING, MENU_SENS_DT_PAIR, NULL,               NULL },
  { TXT_DISPLAY,          MENU_ROOT,         MENU_MAIN_INFO,     MENU_MAIN_SENSORS, MENU_DISP_BRIGHT,  NULL,               NULL },
  { TXT_INFORMATION,      MENU_ROOT,         MENU_MAIN_COOLING,  MENU_MAIN_DISPLAY, MENU_INFO_TIME,    NULL,               NULL },

  // Cooling submenu

  { TXT_FANS_ENABLED,     MENU_MAIN_COOLING, MENU_COOL_MODE,     MENU_KEEP_SPEED,      -1,             &varCoolingEnabled, NULL },
  { TXT_MODE_ONCE_COOLED, MENU_MAIN_COOLING, MENU_TARGET_DT,     MENU_COOL_ENABLED,    -1,             &varCoolingMode,    &GetCoolingModeStr },
  { TXT_TARGET_DT,        MENU_MAIN_COOLING, MENU_COOL_SPDED,    MENU_COOL_MODE,       -1,             &varTargetDeltaT,   NULL },
  { TXT_COOLING_SPEED,    MENU_MAIN_COOLING, MENU_KEEP_SPEED,    MENU_TARGET_DT,       -1,             &varCoolingSpeed,   NULL },
  { TXT_KEEPING_SPEED,    MENU_MAIN_COOLING, MENU_COOL_ENABLED,  MENU_COOL_SPDED,      -1,             &varKeepingSpeed,   NULL },

  // Sensors submenu

  { TXT_SENS_DT_PAIR,     MENU_MAIN_SENSORS, MENU_ASSIGN_SENSORS,MENU_ASSIGN_SENSORS,  -1,             &varDtSecondSensor, &GetSensorPairStr  },
  { TXT_ASSIGN_SENSORS,   MENU_MAIN_SENSORS, MENU_SENS_DT_PAIR,  MENU_SENS_DT_PAIR,    MENU_SENS_MIRR, NULL,               NULL },

  // Display submenu

  { TXT_DISPLAY_BRIGHT,   MENU_MAIN_DISPLAY, MENU_DISP_CONTRAST, MENU_DISP_TEST,       -1,             &varDisplayBright,  NULL },
  { TXT_DISPLAY_CONTRAST, MENU_MAIN_DISPLAY, MENU_DISP_TIMEOUT,  MENU_DISP_BRIGHT,     -1,             &varDisplayContr,   NULL },
  { TXT_DISPLAY_TIMEOUT,  MENU_MAIN_DISPLAY, MENU_DISP_TEST,     MENU_DISP_CONTRAST,   -1,             &varDisplayTimeout, NULL },
  { TXT_DISPLAY_TEST,     MENU_MAIN_DISPLAY, MENU_DISP_BRIGHT,   MENU_DISP_TIMEOUT,    -1,             NULL,               NULL },

  // Info submenu

  { TXT_TIME_SINCE_START, MENU_MAIN_INFO,    MENU_FAN_ALARM,     MENU_INFO_ABOUT,      -1,             NULL,               &GetTimeStr        },
  { TXT_FAN_STUCK_ALARM,  MENU_MAIN_INFO,    MENU_BATT_ALARM,    MENU_INFO_TIME,       -1,             &varFanStuckAlarm,  NULL               },
  { TXT_LOW_BATT_ALARM,   MENU_MAIN_INFO,    MENU_BATT_VOLTAGE,  MENU_FAN_ALARM,       -1,             &varLowBattAlarm,   NULL               },
  { TXT_BATT_ALARM_VOLT,  MENU_MAIN_INFO,    MENU_INFO_VOLTAGE,  MENU_BATT_ALARM,      -1,             &varBattAlarmVolt,  NULL               },
  { TXT_POWER_VOLTAGE,    MENU_MAIN_INFO,    MENU_INFO_ABOUT,    MENU_BATT_VOLTAGE,    -1,             NULL,               &GetVoltageStr     },
  { TXT_ABOUT,            MENU_MAIN_INFO,    MENU_INFO_TIME,     MENU_INFO_VOLTAGE,    -1,             NULL,               &GetAboutStr       },

  // Assign sensors sub-submenu

  { TXT_MIRROR,           MENU_ASSIGN_SENSORS,  MENU_SENS_TUBE,  MENU_SENS_EXT,        -1,             &varSensor0Index,   NULL },
  { TXT_TUBE,             MENU_ASSIGN_SENSORS,  MENU_SENS_AMB,   MENU_SENS_MIRR,       -1,             &varSensor1Index,   NULL },
  { TXT_AMBIENT,          MENU_ASSIGN_SENSORS,  MENU_SENS_EXT,   MENU_SENS_TUBE,       -1,             &varSensor2Index,   NULL },
  { TXT_EXTERNAL,         MENU_ASSIGN_SENSORS,  MENU_SENS_MIRR,  MENU_SENS_AMB,        -1,             &varSensor3Index,   NULL }
};

//------------------------------------------------------------------------------------------
// Romoves node from the menu tree. To restore, reboot is needed.

void  CMenu::HideNode(int id)
{
  CMenuNode & n = node[id];

  node[n.prev].next = n.next;
  node[n.next].prev = n.prev;

  if (n.parent != MENU_ROOT)
  {
    if (node[n.parent].child == id)
        node[n.parent].child = n.next;
  }
}

//------------------------------------------------------------------------------------------

void  CMenu::onHold()
{
  if (!inMenu)
    varCoolingEnabled.inc();

  if (varCoolingEnabled.value == 1)
    fans.PauseStuckDetection();

  ShowMessage(
    LoadMessage((varCoolingEnabled.value == 1) ? TXT_FANS_ENABLED : TXT_FANS_DISABLED),
    nullptr,
    MSG_LONG_TIME,
    false);
}

//------------------------------------------------------------------------------------------

void  CMenu::onNext()
{
  if (inMenu)
  {
    if (inLeaf)
    {
      // change the variable
      if (node[menuPos].var != NULL)
        node[menuPos].var->inc();
    }
    else
    {
      // go to the next submenu
      menuPos = node[menuPos].next;
    }
  }
  else
  {
    varComboInfoMode.inc();
  }
}

//------------------------------------------------------------------------------------------

void  CMenu::onPrev()
{
  if (inMenu)
  {
    if (inLeaf)
    {
      // change the variable
      if (node[menuPos].var != NULL)
        node[menuPos].var->dec();
    }
    else
    {
      // go to the previous submenu
      menuPos = node[menuPos].prev;
    }
  }
  else
  {
    varComboInfoMode.dec();
  }
}

//------------------------------------------------------------------------------------------

void  CMenu::onEnter()
{
  if (!inMenu)
  {
    // enter menu
    inMenu = true;
    menuPos = 0;
  }
  else
  {
    if (node[menuPos].child == -1)
    {
      // enter the variable edit level
      inLeaf = true;
    }
    else
    {
      // enter the children submenu
      inLeaf = false;
      menuPos = node[menuPos].child;
    }
  }
}

//------------------------------------------------------------------------------------------

void  CMenu::onBack()
{
  /*if (!inMenu)
  {
    // enter menu
    inMenu = true;
    menuPos = 0;
  }
  else*/
  {
    if (inLeaf)
    {
      // exit the variable edit level
      inLeaf = false;
    }
    else
    {
      if (node[menuPos].parent != -1)
      {
        // go to the parent sebmenu
        menuPos = node[menuPos].parent;
      }
      else
      {
        // exit menu
        inMenu = false;

        // saving variables to EEPROM if powered by USB
        if (settings.isPoweredByUSB())
          settings.Save();
      }
    }
  }
}

//------------------------------------------------------------------------------------------

void  CMenu::ShowMessage(const char * line0, const char * line1, uint32_t timeout, bool blink)
{
  strcpy(msgLine0, line0);
  strcpy(msgLine1, line1);
  msgBlink    = blink;
  msgTimeout  = timeout;
  msgShowTick = millis();
}

//------------------------------------------------------------------------------------------

const char * CMenu::GetLine0()
{
  uint32_t t = millis();

  if (inMenu)
  {
    const CMenuNode & n = node[menuPos];
  
    if (inLeaf)
      return LoadMessage(n.name);
    else
    {
      if (n.parent == -1)
        return LoadMessage(TXT_SETTINGS);
      else
        return LoadMessage(node[n.parent].name);
    }
  }
  else if (t - msgShowTick <= msgTimeout)
  {
    bool blink = msgBlink && (((t / MSG_BLINK_HALFPERIOD) & 1) == 1);
    return (blink || (msgLine0 == nullptr)) ? "" : msgLine0;
  }
  else
  {
    switch (varComboInfoMode.value)
    {
      case D_TEMP_STYLE_1:      return state.GetTempStr0();           break;
      case D_COMBO_STYLE_1:     return state.GetComboStr0();          break;
      case D_COMBO_STYLE_2:     return state.GetComboStr0();          break;
      case D_TEMP_FANS_STYLE_1: return state.GetTempFansStr0Style1(); break;
      case D_TEMP_FANS_STYLE_2: return state.GetTempFansStr0Style2(); break;
      case D_FANS:              return state.GetFansStr0();           break;
      default:                  return "";                            break;
    }
  }
}

//------------------------------------------------------------------------------------------

const char * CMenu::GetLine1()
{
  uint32_t t = millis();

  if (inMenu)
  {
    const CMenuNode & n = node[menuPos];
  
    if (inLeaf)
    {
      if (n.getStrFunc != NULL)
        return n.getStrFunc();
      else if (n.var != NULL)
        return n.var->getValueStr();
      else
        return "";
    }
    else
        return LoadMessage(n.name);
  }
  else if (t - msgShowTick <= msgTimeout)
  {
    bool blink = msgBlink && (((t / MSG_BLINK_HALFPERIOD) & 1) == 1);
    return (blink || (msgLine1 == nullptr)) ? "" : msgLine1;
  }
  else
  {
    switch (varComboInfoMode.value)
    {
      case D_TEMP_STYLE_1:      return state.GetTempStr1();           break;
      case D_COMBO_STYLE_1:     return state.GetComboStr1Style1();    break;
      case D_COMBO_STYLE_2:     return state.GetComboStr1Style2();    break;
      case D_TEMP_FANS_STYLE_1: return state.GetTempFansStr1Style1(); break;
      case D_TEMP_FANS_STYLE_2: return state.GetTempFansStr1Style2(); break;
      case D_FANS:              return state.GetFansStr1();           break;
      default:                  return "";                            break;
    }
  }
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
    case C_COOL_AND_STOP: return LoadMessage(TXT_STOP);
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
  if (settings.isPoweredByUSB())
    return LoadMessage2(TXT_POWERED_BY_USB);
  else
  {
    sprintf(text, "%4.2f V", settings.GetVoltage());
    return text;
  }
}

//------------------------------------------------------------------------------------------

const char * GetAboutStr()
{
  return LoadMessage2(TXT_COPYRIGHT);
}

//------------------------------------------------------------------------------------------
