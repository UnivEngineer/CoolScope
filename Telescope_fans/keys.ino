//------------------------------------------------------------------------------------------
// Keyboard
//------------------------------------------------------------------------------------------
#include "keys.h"
//------------------------------------------------------------------------------------------
CKeyboard keys;
//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------

CButton::CButton(byte p, bool rep)
{
  repeating   = rep;
  isClickFlag = false;
  isHoldFlag  = false;
  pin = p;
  pinMode(pin, INPUT_PULLUP);
}

//------------------------------------------------------------------------------------------

void  CButton::update()
{
  uint32_t t = millis();
  uint32_t passed = t - tmr;

  bool contactUp = digitalRead(pin); // inverse, false == pressed

  if (!contactUp && !contactFlag && (passed >= BTN_DEBOUNCE_DELAY))
  {
    tmr = t;
    contactFlag = true;
    isClickFlag = true;
    return;
  }

  if (!contactUp && contactFlag && (passed >= BTN_HOLD_DELAY))
  {
    tmr = t;
    isHoldFlag = true;
    return;
  }

  if (repeating && !contactUp && contactFlag && (passed >= BTN_REPEAT_PERIOD))
  {
    tmr = t;
    isClickFlag = true;
    return;
  }

  if (contactUp && contactFlag)
  {
    tmr = t;
    contactFlag = false;
  }

  isClickFlag = false;
  isHoldFlag  = false;
}

//------------------------------------------------------------------------------------------

bool CButton::isClick()
{
  return isClickFlag;
}

//------------------------------------------------------------------------------------------

bool CButton::isHeld()
{
  return isHoldFlag;
}

//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------

CKeyboard::CKeyboard():
Button{ { KEY_MENU_PIN, false }, { KEY_PREV_PIN, true }, { KEY_NEXT_PIN, true }, { KEY_ENTER_PIN, false } }
{
}

//------------------------------------------------------------------------------------------

void  CKeyboard::update()
{
  for (int i=0; i<BT_COUNT; ++i)
    Button[i].update();
}

//------------------------------------------------------------------------------------------

bool  CKeyboard::isClickedAny()
{
  for (int i=0; i<BT_COUNT; ++i)
    if (Button[i].isClick()) return true;
  return false;
}

//------------------------------------------------------------------------------------------
