#ifndef FANS_H
#define FANS_H
//------------------------------------------------------------------------------------------
// PWM fans
//------------------------------------------------------------------------------------------
#include <util/atomic.h>
//------------------------------------------------------------------------------------------

class CFansController
{
public:
  CFansController(){};

  void  Init();
  void  Update();
  void  Off();
  bool  isStuck();

  bool  fanStuck1 = false;
  bool  fanStuck2 = false;

private:
  void  setupTimer1();
  void  setupTimer2();
  void  setPWM1A(int duty);
  void  setPWM1B(int duty);
  void  setPWM2 (int duty);

  static   void tach1ISR();
  static   void tach2ISR();

  static uint32_t volatile fanCounter1;
  static uint32_t volatile fanCounter2;
  uint32_t lastTimeRPM = 0;
  uint32_t lastTimeStuck = 0;
};

//------------------------------------------------------------------------------------------
extern  CFansController fans;
//------------------------------------------------------------------------------------------
#endif // FANS_H
