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
// Special characters
#ifdef GRAPHICS_MODE

#define BAR   "\x10"
#define DELTA "\x7F"
#define DEG   "\x80"
#define BATT  "\x81"
#define FAN1  "\x82"
#define FAN2  "\x83"
#define FAN3  "\x84"

#else

#define DEG   "\x01"
#define DELTA "\x02"
#define BATT  "\x03"
#define FAN1  "\x04"
#define FAN2  "\x05"
#define FAN3  "\x06"
#define BAR   "\xFF"

#endif
//------------------------------------------------------------------------------------------
// Interface messages
//------------------------------------------------------------------------------------------

enum  CTextMessageId
{
  TXT_SETTINGS = 0,
  TXT_COOLING,
  TXT_DISPLAY,
  TXT_INFORMATION,
  TXT_FAN_1_STUCK,
  TXT_FAN_2_STUCK,
  TXT_KEEP_DT,
  TXT_KEEP_BLOWING,
  TXT_KEEP_DRAWING,
  TXT_STOP,
  TXT_COOLING_OFF,
  TXT_COPYRIGHT,
  TXT_MODE_ONCE_COOLED,
  TXT_TARGET_DT,
  TXT_COOLING_SPEED,
  TXT_KEEPING_SPEED,
  TXT_DISPLAY_BRIGHT,
  TXT_DISPLAY_CONTRAST,
  TXT_DISPLAY_TIMEOUT,
  TXT_FAN_STUCK_ALARM,
  TXT_TIME_SINCE_START,
  TXT_POWER_VOLTAGE,
  TXT_ABOUT,
  TXT_SENSORS,
  TXT_SENS_DT_PAIR,
  TXT_ASSIGN_SENSORS,
  TXT_MIRROR,
  TXT_TUBE,
  TXT_AMBIENT,
  TXT_EXTERNAL,
  TXT_MIRR_AND_TUBE,
  TXT_MIRR_AND_AMB,
  TXT_MIRR_AND_EXT,
  TXT_NOT_ASSIGNED,
  TXT_ERROR,
  TXT_LOGO,
  TXT_VER_OLED,
  TXT_VER_LCD,
  TXT_DISPLAY_TEST,
  TXT_POWERED_BY_USB,
  TXT_LOW_BATT_ALARM,
  TXT_BATT_ALARM_VOLT,
  TXT_LOW_BATTERY,
  TXT_FANS_ENABLED,
  TXT_FANS_DISABLED
};

//------------------------------------------------------------------------------------------
//     Char number (max 16): "0123456789ABCDEF"
const char mes00[] PROGMEM = "Settings";
const char mes01[] PROGMEM = "Cooling";
const char mes02[] PROGMEM = "Display";
const char mes03[] PROGMEM = "Information";
const char mes04[] PROGMEM = "Front fan stuck!";
const char mes05[] PROGMEM = " Rear fan stuck!";
const char mes06[] PROGMEM = "Keep " DELTA "T";
const char mes07[] PROGMEM = "Keep blowing";
const char mes08[] PROGMEM = "Keep drawing";
const char mes09[] PROGMEM = "Stop";
const char mes10[] PROGMEM = "Cooling is off";
const char mes11[] PROGMEM = "(C)SpaceEnigneer";
const char mes12[] PROGMEM = "Mode once cooled";
const char mes13[] PROGMEM = "Target " DELTA "T";
const char mes14[] PROGMEM = "Cooling speed";
const char mes15[] PROGMEM = "Keeping speed";
const char mes16[] PROGMEM = "Brightness";
const char mes17[] PROGMEM = "Contrast";
const char mes18[] PROGMEM = "Timeout";
const char mes19[] PROGMEM = "Fan stuck alarm";
const char mes20[] PROGMEM = "Uptime";            // "Time since start";
const char mes21[] PROGMEM = "Power voltage";
const char mes22[] PROGMEM = "About";
const char mes23[] PROGMEM = "Sensors";
const char mes24[] PROGMEM = "Target " DELTA "T pair";
const char mes25[] PROGMEM = "Assign sensors";
const char mes26[] PROGMEM = "Mirror";
const char mes27[] PROGMEM = "Tube";
const char mes28[] PROGMEM = "Ambient";
const char mes29[] PROGMEM = "External";
const char mes30[] PROGMEM = "Mirror & tube";
const char mes31[] PROGMEM = "Mirror & ambient";
const char mes32[] PROGMEM = "Mirror & extrnal";
const char mes33[] PROGMEM = "< Not assigned >";
const char mes34[] PROGMEM = "Error";
const char mes35[] PROGMEM = "-= COOL SCOPE =-";
const char mes36[] PROGMEM = "v1.3 OLED";
const char mes37[] PROGMEM = "v1.3 LCD";
const char mes38[] PROGMEM = "Test";
const char mes39[] PROGMEM = "Powered by USB";
const char mes40[] PROGMEM = "Low batt. alarm";
const char mes41[] PROGMEM = "Batt. alarm volt";
const char mes42[] PROGMEM = "Battery is low!";
const char mes43[] PROGMEM = "Fans enabled";
const char mes44[] PROGMEM = "Fans disabled";

//------------------------------------------------------------------------------------------
const char * const mes_table[] PROGMEM =
{
  mes00, mes01, mes02, mes03, mes04, mes05, mes06, mes07, mes08, mes09,
  mes10, mes11, mes12, mes13, mes14, mes15, mes16, mes17, mes18, mes19,
  mes20, mes21, mes22, mes23, mes24, mes25, mes26, mes27, mes28, mes29,
  mes30, mes31, mes32, mes33, mes34, mes35, mes36, mes37, mes38, mes39,
  mes40, mes41, mes42, mes43, mes44
};
//------------------------------------------------------------------------------------------
const char * LoadMessage (CTextMessageId n);
const char * LoadMessage2(CTextMessageId n);
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
#else
  static uint8_t CustomChars[][8];
#endif

  void  SetTextMode();
  void  SetGraphMode();

  uint32_t lastOnTime = 0;
  int      testPos = 0;

  void  AppendWithSpaces(char * text, int len);

  char  memLine[2][17];

public:

  bool isOLED = false; // true for Winstar 1602 OLED
  bool isOff  = false;

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
  void  Clear();
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
