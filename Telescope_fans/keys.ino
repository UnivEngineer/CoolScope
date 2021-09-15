//------------------------------------------------------------------------------------------
// Keyboard
//------------------------------------------------------------------------------------------
#include "keys.h"
//------------------------------------------------------------------------------------------
CButton  BackButton (KEY_MENU_PIN,  false);
CButton  PrevButton (KEY_PREV_PIN,  true);
CButton  NextButton (KEY_NEXT_PIN,  true);
CButton  EnterButton(KEY_ENTER_PIN, false);
//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------
#define BTN_DEBOUNCE_DELAY 50  // ms
#define BTN_REPEAT_PERIOD  200 // ms
//------------------------------------------------------------------------------------------

CButton::CButton(byte p, bool rep)
{
  repeating = rep;
  pin = p;
  pinMode(pin, INPUT_PULLUP);
}

//------------------------------------------------------------------------------------------

bool CButton::isClick()
{
  uint32_t t = millis();

  bool btnState = digitalRead(pin);

  if (!btnState && !flag && (t - tmr >= BTN_DEBOUNCE_DELAY))
  {
    flag = true;
    tmr = t;
    return true;
  }

  if (repeating && (!btnState && flag && (t - tmr >= BTN_REPEAT_PERIOD)))
  {
    tmr = t;
    return true;
  }

  if (btnState && flag)
  {
    flag = false;
    tmr = t;
  }

  return false;
}

//------------------------------------------------------------------------------------------
