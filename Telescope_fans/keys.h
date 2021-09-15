#ifndef KEYS_H
#define KEYS_H
//------------------------------------------------------------------------------------------
// Keyboard
//------------------------------------------------------------------------------------------
#define K_REPEAT 1
//------------------------------------------------------------------------------------------

class CButton
{
  byte     pin;
  uint32_t tmr;
  bool     flag;
  bool     repeating;

public:
  CButton(byte p, bool rep);
  bool isClick();
};

//------------------------------------------------------------------------------------------
extern  CButton  BackButton;
extern  CButton  PrevButton;
extern  CButton  NextButton;
extern  CButton  EnterButton;
//------------------------------------------------------------------------------------------
#endif // KEYS_H
