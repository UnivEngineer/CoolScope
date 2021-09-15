#ifndef DISPLAY_H
#define DISPLAY_H
//------------------------------------------------------------------------------------------
// 1602 text display
//------------------------------------------------------------------------------------------
#include <LiquidCrystal.h>
//------------------------------------------------------------------------------------------
// Special characters
#define DEG   "\01"
#define DELTA "\02"
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
//------------------------------------------------------------------------------------------
const char * const mes_table[] PROGMEM =
{
  mes00, mes01, mes02, mes03, mes04, mes05, mes06, mes07, mes08, mes09,
  mes10, mes11, mes12, mes13, mes14, mes15, mes16, mes17, mes18, mes19,
  mes20, mes21, mes22, mes23, mes24, mes25, mes26, mes27, mes28, mes29,
  mes30, mes31, mes32, mes33, mes34
};
//------------------------------------------------------------------------------------------
const char * LoadMessage(CTextMessageId n);
//------------------------------------------------------------------------------------------

class CDisplay
{
  LiquidCrystal lcd;

  static const uint32_t MinContrDutyLCD   = 100; // Min workable LCD contrast  value (PWM duty)
  static const uint32_t MaxContrDutyLCD   = 255; // Max workable LCD contrast  value (PWM duty)
  static const uint32_t MinBrightDutyLCD  =   0; // Min workable LCD backlingt value (PWM duty)
  static const uint32_t MaxBrightDutyLCD  = 255; // Max workable LCD backlingt value (PWM duty)
  static const uint32_t MaxBrightDutyOLED =  80; // Max workable OLED dimming  value (PWM duty), OLED brightness is inverted

  static const int NCustomChars = 21;
  static uint8_t CustomChars[NCustomChars][8];

  void  SetTextMode();
  void  SetGraphMode();

  unsigned long lastOnTime = 0;

  void  AppendWithSpaces(char * text, int len);

public:

  bool isOLED = false; // true for Winstar 1602 OLED
  bool isOff  = false;

  CDisplay(): lcd(LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN) {};

  void  Init();
  void  SetBrightAndContrast();
  void  Update();
  void  Touch();
  void  On();
  void  Off(bool hard);
};

//------------------------------------------------------------------------------------------
extern  CDisplay display;
//------------------------------------------------------------------------------------------
#endif // DISPLAY_H
