#ifndef DISPLAY_H
#define DISPLAY_H
//------------------------------------------------------------------------------------------
// 1602 text display
//------------------------------------------------------------------------------------------
//#define OLED_I2C
#ifdef OLED_I2C
#include <LiquidCrystal_PCF8574.h>
#else
#include <LiquidCrystal.h>
#endif
//------------------------------------------------------------------------------------------

class CDisplay
{
#ifdef OLED_I2C
  //LiquidCrystal_I2C lcd;
  LiquidCrystal_PCF8574 lcd;
#else
  LiquidCrystal lcd;
#endif

  static const uint32_t MinContrDutyLCD   = 100; // Min workable LCD contrast  value (PWM duty)
  static const uint32_t MaxContrDutyLCD   = 255; // Max workable LCD contrast  value (PWM duty)
  static const uint32_t MinBrightDutyLCD  =   0; // Min workable LCD backlingt value (PWM duty)
  static const uint32_t MaxBrightDutyLCD  = 255; // Max workable LCD backlingt value (PWM duty)
  static const uint32_t MaxBrightDutyOLED =  80; // Max workable OLED dimming  value (PWM duty), OLED brightness is inverted

#ifdef GRAPHICS_MODE
  uint32_t  lastSaverTime = 0;
  int       saverShiftX = 0;
  int       saverShiftY = 0;
  char      memLine[2][17];
#else
  static uint8_t CustomChars[][8];
#endif

  void  SetTextMode();
  void  SetGraphMode();

  uint32_t lastOnTime = 0;
  int      testPos = 0;

  void  AppendWithSpaces(char * text, int len);

public:

  bool isOLED = false; // true for Winstar 1602 OLED
  bool isOff  = false;
  bool isTest = false;

#ifdef OLED_I2C
  //CDisplay(): lcd(0x3C, 16, 2) {};
  CDisplay(): lcd(0x3C) {};
#else
  CDisplay(): lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN) {};
#endif

  void  Init();
  void  SetBrightAndContrast();
  void  Update();
  void  Touch();
  void  On();
  void  Off(bool hard);
  void  Clear(bool clearScreen);
  void  Test();

  // Wrapper for LiquidCrystal or internal implementation of text print for graphicsl Winstar displays
  void  PrintText(int x, int y, const char * text);

  // Prints only changes in the line y
  void  PrintLineSmart(int y, const char * text);

private:
  // Internal implementation of text print for graphicsl Winstar displays
  void  SetGraphCursor(int x, int y);
  void  SetTextCursor (int x, int y);
  int   GetCharIndex(uint8_t c);
  void  PrintChar(int x, int y, char c);
};

//------------------------------------------------------------------------------------------
extern  CDisplay display;
//------------------------------------------------------------------------------------------
#endif // DISPLAY_H
