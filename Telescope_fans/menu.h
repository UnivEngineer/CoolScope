#ifndef MENU_H
#define MENU_H
//------------------------------------------------------------------------------------------
// menu
//------------------------------------------------------------------------------------------
#include "vars.h"
//------------------------------------------------------------------------------------------

enum  CMenuNodeID
{
  MENU_ROOT = -1,

  MENU_MAIN_COOLING,
  MENU_MAIN_SENSORS,
  MENU_MAIN_DISPLAY,
  MENU_MAIN_INFO,

  MENU_COOL_ENABLED,
  MENU_COOL_MODE,
  MENU_TARGET_DT,
  MENU_COOL_SPDED,
  MENU_KEEP_SPEED,

  MENU_SENS_DT_PAIR,
  MENU_ASSIGN_SENSORS,

  MENU_DISP_BRIGHT,
  MENU_DISP_CONTRAST,
  MENU_DISP_TIMEOUT,
  MENU_DISP_TEST,

  MENU_INFO_TIME,
  MENU_FAN_ALARM,
  MENU_BATT_ALARM,
  MENU_BATT_VOLTAGE,
  MENU_INFO_VOLTAGE,
  MENU_INFO_ABOUT,

  MENU_SENS_MIRR,
  MENU_SENS_TUBE,
  MENU_SENS_AMB,
  MENU_SENS_EXT
};

//------------------------------------------------------------------------------------------

struct  CMenuNode
{
  CTextMessageId  name;
  int             parent;
  int             next;
  int             prev;
  int             child;
  CVariable     * var;
  const char    * (*getStrFunc)(void);
};

//------------------------------------------------------------------------------------------

class CMenu
{
  static CMenuNode node[];

  int  menuPos   = 0;
  bool inLeaf    = false;
  bool inMenu    = false;

  uint32_t  msgShowTick = 0;
  uint32_t  msgTimeout  = 0;
  bool      msgBlink;
  char      msgLine0[LINE_LENGTH+1];
  char      msgLine1[LINE_LENGTH+1];

public:
  CMenu() {};

  void  HideNode(int index);
  bool  isDisplayTest() { return inLeaf && (menuPos == MENU_DISP_TEST); }

  void  onHold();

  void  onNext();
  void  onPrev();
  void  onEnter();
  void  onBack();

  void  ShowMessage(const char * line0, const char * line1, uint32_t timeout, bool blink);

  const char * GetLine0();
  const char * GetLine1();
};

//------------------------------------------------------------------------------------------
extern CMenu  menu;
//------------------------------------------------------------------------------------------
const char * GetCoolingModeStr();
const char * GetTimeStr();
const char * GetVoltageStr();
const char * GetAboutStr();
const char * GetSensorPairStr();
//------------------------------------------------------------------------------------------
#endif // MENU_H
