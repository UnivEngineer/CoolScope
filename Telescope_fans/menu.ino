//------------------------------------------------------------------------------------------
// menu
//------------------------------------------------------------------------------------------
#include "vars.h"
//------------------------------------------------------------------------------------------
CMenu menu;
//------------------------------------------------------------------------------------------

CMenuNode CMenu::node[] =
{
  // name,                parent,            next,               prev,              child,            var,                getStrFunc

  // Main menu

  { TXT_COOLING,          MENU_ROOT,         MENU_MAIN_DISPLAY,  MENU_MAIN_INFO,    MENU_COOL_MODE,   NULL,               NULL },
  { TXT_DISPLAY,          MENU_ROOT,         MENU_MAIN_SENSORS,  MENU_MAIN_COOLING, MENU_DISP_BRIGHT, NULL,               NULL },
  { TXT_SENSORS,          MENU_ROOT,         MENU_MAIN_INFO,     MENU_MAIN_DISPLAY, MENU_SENS_DT_PAIR,NULL,               NULL },
  { TXT_INFORMATION,      MENU_ROOT,         MENU_MAIN_COOLING,  MENU_MAIN_SENSORS, MENU_INFO_TIME,   NULL,               NULL },

  // Cooling submenu

  { TXT_MODE_ONCE_COOLED, MENU_MAIN_COOLING, MENU_TARGET_DT,     MENU_KEEP_SPEED,      -1,            &varCoolingMode,    &GetCoolingModeStr },
  { TXT_TARGET_DT,        MENU_MAIN_COOLING, MENU_COOL_SPDED,    MENU_COOL_MODE,       -1,            &varTargetDeltaT,   NULL },
  { TXT_COOLING_SPEED,    MENU_MAIN_COOLING, MENU_KEEP_SPEED,    MENU_TARGET_DT,       -1,            &varCoolingSpeed,   NULL },
  { TXT_KEEPING_SPEED,    MENU_MAIN_COOLING, MENU_COOL_MODE,     MENU_COOL_SPDED,      -1,            &varKeepingSpeed,   NULL },

  // Display submenu

  { TXT_DISPLAY_BRIGHT,   MENU_MAIN_DISPLAY, MENU_DISP_CONTRAST, MENU_DISP_TIMEOUT,    -1,            &varDisplayBright,  NULL },
  { TXT_DISPLAY_CONTRAST, MENU_MAIN_DISPLAY, MENU_DISP_TIMEOUT,  MENU_DISP_BRIGHT,     -1,            &varDisplayContr,   NULL },
  { TXT_DISPLAY_TIMEOUT,  MENU_MAIN_DISPLAY, MENU_DISP_BRIGHT,   MENU_DISP_CONTRAST,   -1,            &varDisplayTimeout, NULL },

  // Sensors submenu

  { TXT_SENS_DT_PAIR,     MENU_MAIN_SENSORS, MENU_ASSIGN_SENSORS,MENU_ASSIGN_SENSORS,  -1,            &varDtSecondSensor, &GetSensorPairStr  },
  { TXT_ASSIGN_SENSORS,   MENU_MAIN_SENSORS, MENU_SENS_DT_PAIR,  MENU_SENS_DT_PAIR,    MENU_MIRROR,   NULL,               NULL },

  // Info submenu

  { TXT_TIME_SINCE_START, MENU_MAIN_INFO,    MENU_INFO_VOLTAGE,  MENU_INFO_ABOUT,      -1,            NULL,               &GetTimeStr        },
  { TXT_POWER_VOLTAGE,    MENU_MAIN_INFO,    MENU_FAN_ALARM,     MENU_INFO_TIME,       -1,            NULL,               &GetVoltageStr     },
  { TXT_FAN_STUCK_ALARM,  MENU_MAIN_INFO,    MENU_INFO_ABOUT,    MENU_INFO_VOLTAGE,    -1,            &varFanStuckAlarm,  NULL               },
  { TXT_ABOUT,            MENU_MAIN_INFO,    MENU_INFO_TIME,     MENU_FAN_ALARM,       -1,            NULL,               &GetAboutStr       },

  // Assign sensors sub-submenu

  { TXT_MIRROR,           MENU_ASSIGN_SENSORS,  MENU_TUBE,       MENU_EXTERNAL,        -1,            &varSensor0Index,   NULL },
  { TXT_TUBE,             MENU_ASSIGN_SENSORS,  MENU_AMBIENT,    MENU_MIRROR,          -1,            &varSensor1Index,   NULL },
  { TXT_AMBIENT,          MENU_ASSIGN_SENSORS,  MENU_EXTERNAL,   MENU_TUBE,            -1,            &varSensor2Index,   NULL },
  { TXT_EXTERNAL,         MENU_ASSIGN_SENSORS,  MENU_MIRROR,     MENU_AMBIENT,         -1,            &varSensor3Index,   NULL }
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
  if (!inMenu)
  {
    // enter menu
    inMenu = true;
    menuPos = 0;
  }
  else
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

const char * CMenu::GetComboLine0()
{
  if (fans.isStuck())
  {
    bool blink = ((millis() / 500) & 1) == 0;
    if (blink && fans.fanStuck1)
      return LoadMessage(TXT_FAN_1_STUCK);
    else if (blink && fans.fanStuck2)
      return LoadMessage(TXT_FAN_2_STUCK);
    else
      return "";
  }
  else
  {
    switch (varComboInfoMode.value)
    {
      case D_TEMP_STYLE_1:      return state.GetTempStyle1Str0();     break;
      case D_TEMP_FANS_STYLE_1: return state.GetTempFansStyle1Str0(); break;
      case D_TEMP_FANS_STYLE_2: return state.GetTempFansStyle2Str0(); break;
      case D_FANS:              return state.GetFansStr0();           break;
      default:                  return "";                            break;
    }
  }
}

//------------------------------------------------------------------------------------------

const char * CMenu::GetComboLine1()
{
  if (fans.isStuck())
  {
    bool blink = ((millis() / 500) & 1) == 0;
    if (blink && fans.fanStuck1 && fans.fanStuck2)
      return LoadMessage(TXT_FAN_2_STUCK);
    else
      return "";
  }
  else
  {
    switch (varComboInfoMode.value)
    {
      case D_TEMP_STYLE_1:      return state.GetTempStyle1Str1();     break;
      case D_TEMP_FANS_STYLE_1: return state.GetTempFansStyle1Str1(); break;
      case D_TEMP_FANS_STYLE_2: return state.GetTempFansStyle2Str1(); break;
      case D_FANS:              return state.GetFansStr1();           break;
      default:                  return "";                            break;
    }
  }
}

//------------------------------------------------------------------------------------------

const char * CMenu::GetLine0()
{
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
  else
    return GetComboLine0();
}

//------------------------------------------------------------------------------------------

const char * CMenu::GetLine1()
{
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
  else
    return GetComboLine1();
}

//------------------------------------------------------------------------------------------
