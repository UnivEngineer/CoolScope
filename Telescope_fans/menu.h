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
  MENU_MAIN_DISPLAY,
  MENU_MAIN_SENSORS,
  MENU_MAIN_INFO,

  MENU_COOL_MODE,
  MENU_TARGET_DT,
  MENU_COOL_SPDED,
  MENU_KEEP_SPEED,

  MENU_DISP_BRIGHT,
  MENU_DISP_CONTRAST,
  MENU_DISP_TIMEOUT,

  MENU_SENS_DT_PAIR,
  MENU_ASSIGN_SENSORS,

  MENU_INFO_TIME,
  MENU_INFO_VOLTAGE,
  MENU_FAN_ALARM,
  MENU_INFO_ABOUT,

  MENU_MIRROR,
  MENU_TUBE,
  MENU_AMBIENT,
  MENU_EXTERNAL
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

  const char * GetComboLine0();
  const char * GetComboLine1();

public:
  CMenu() {};

  void  HideNode(int index);

  void  onNext();
  void  onPrev();
  void  onEnter();
  void  onBack();

  const char * GetLine0();
  const char * GetLine1();
};

//------------------------------------------------------------------------------------------
extern CMenu  menu;
//------------------------------------------------------------------------------------------
#endif // MENU_H
