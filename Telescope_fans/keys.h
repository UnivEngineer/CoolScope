#ifndef KEYS_H
#define KEYS_H
//------------------------------------------------------------------------------------------
// Keyboard
//------------------------------------------------------------------------------------------
#define BTN_DEBOUNCE_DELAY   50 // ms
#define BTN_REPEAT_PERIOD   200 // ms
#define BTN_HOLD_DELAY     2000 // ms
//------------------------------------------------------------------------------------------

class CButton
{
  byte     pin;
  uint32_t tmr;
  
  bool     repeating    : 1;
  bool     contactFlag  : 1;
  bool     isClickFlag  : 1;
  bool     isHoldFlag   : 1;

public:
  CButton(byte p, bool rep);
  void  update();
  bool  isClick();
  bool  isHeld();
};

//------------------------------------------------------------------------------------------

enum  CButtonID
{
  BT_MENU = 0,
  BT_PREV,
  BT_NEXT,
  BT_ENTER,
  BT_COUNT
};

//------------------------------------------------------------------------------------------

class CKeyboard
{
public:
  CButton  Button[BT_COUNT];
  CKeyboard();
  void  update();
  bool  isClickedAny();
};

//------------------------------------------------------------------------------------------
extern  CKeyboard keys;
//------------------------------------------------------------------------------------------
#endif // KEYS_H
