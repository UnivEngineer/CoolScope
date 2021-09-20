#define NANO
//------------------------------------------------------------------------------------------
//#define DEBUG
//#define USE_DHT
//#define RUSSIAN
//------------------------------------------------------------------------------------------
#define LINE_LENGTH             16
//------------------------------------------------------------------------------------------
// All times in milliseconds
#define POWER_DETECT_PERIOD     5     // period to measure power voltage and detect power loss
#define MAIN_LOOP_PERIOD        100   // main program loop peroid
#define TEMP_SENSOR_READ_PERIOD 1000  // period to read temperature from sensors
#define POWER_RESTORE_DELAY     500   // wait time before power restored signal
#define FAN_RPM_COUNT_TIME      1000  // period of fan RPM measurement (pulse accumulation)
#define FAN_STUCK_WAIT_TIME     2000  // report fan failure if it don't spin this long
#define FAN_STUCK_IGNORE_TIME   5000  // don't detect fan failure after cooling on/off
#define MSG_SHORT_TIME          100   // short message (blinking alerts) display time
#define MSG_LONG_TIME           2000  // long message ("fans enabled/disbled") display time
#define MSG_BLINK_HALFPERIOD    500   // half of message blinking period
#define EEPROM_WRITE_WAIT_TIME  10000 // delay between writes to EEPROM memory
//------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------
// Used pins
//------------------------------------------------------------------------------------------
// Hardware interupt pins: 2, 3
// Hardware PWM pins:      3, 5, 6, 9, 10, 11
// Analog-read-only pins:  A6(20), A7(21)

#define DHT_PIN           8   // Digital pin connected to the DHT sensor
#define DS18B20_PIN       8   // Digital pin connected to the DS19B20 sensor(s)

#define TACH_1_PIN        2   // Pin for fan 1 tachometer - must be an interrupt capable pin (2 or 3 on Arduino Nano)
#define TACH_2_PIN        3   // Pin for fan 2 tachometer - must be an interrupt capable pin (2 or 3 on Arduino Nano)

#define PWM_1A_PIN        9   // Digital pin for PWM 1A channel
#define PWM_1B_PIN        10  // Digital pin for PWM 1B channel
#define PWM_2_PIN         3   // Digital pin for PWM 2  channel

#define PWM_BRIGHT_LCD    5   // Display brightness PWM
#define PWM_CONTRAST_LCD  6   // Display contrast   PWM

// Digital pins for 1602 disaply
#define LCD_D7_PIN        14  // A0=14
#define LCD_D6_PIN        15  // A1=15
#define LCD_D5_PIN        16  // A2=16
#define LCD_D4_PIN        17  // A3=17
#define LCD_E_PIN         18  // A4=18
#define LCD_RS_PIN        19  // A5=19

#define POWER_DETECT_PIN  A6  // Power loss detection pin

#define LCD_DETECT_PIN    A7  // Display type (LCD/OLED) jumper pin

#define BOARD_LED_PIN     13  // Onboard LED pin

// Digital pins for buttons
#define KEY_MENU_PIN      4
#define KEY_PREV_PIN      7
#define KEY_NEXT_PIN      11
#define KEY_ENTER_PIN     12
//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------
// Used modules
//------------------------------------------------------------------------------------------
#include "temp.h"
#include "vars.h"
#include "settings.h"
#include "state.h"
#include "fans.h"
#include "display.h"
#include "keys.h"
#include "menu.h"
//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------
// Main code
//------------------------------------------------------------------------------------------

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println(F("Starting..."));
#endif

  settings.Init();
  fans.Init();
  display.Init();
  temp.Init();
}

//------------------------------------------------------------------------------------------

void loop()
{
  for (int i = 0; i < MAIN_LOOP_PERIOD / POWER_DETECT_PERIOD; ++i)
  {
    // Detect power loss and save settings to EEPROM
    if (settings.DetectPowerLoss())
    {
      // If power loss detected, first shot down main power consumers
      display.Off(true);
      fans.Off();

      // Then save data to EEPROM - we must have enough charge on the 12V capasitor
      settings.Save();
    }
    
    delay(POWER_DETECT_PERIOD);
  }

  settings.Update(MAIN_LOOP_PERIOD / POWER_DETECT_PERIOD);

  if (!settings.isPowerLost())
  {
    // Read keyboard
    keys.update();

    bool anyKey = keys.isClickedAny();
  
    if (display.isOff && (anyKey || fans.isStuck() || settings.isLowBattery() || settings.isPowerRestored()))
      display.On();
    else
    {
      if (anyKey)
        display.Touch();
  
      if (keys.Button[BT_MENU] .isHeld())  menu.onHold();

      if (keys.Button[BT_MENU] .isClick()) menu.onBack();
      if (keys.Button[BT_PREV] .isClick()) menu.onPrev();
      if (keys.Button[BT_NEXT] .isClick()) menu.onNext();
      if (keys.Button[BT_ENTER].isClick()) menu.onEnter();
    }
  
    // Read temperature sensors
    temp.Update();
  
    // Set fans speed and read fans RPM
    fans.Update();
  
    // Update disaply
    display.Update();
  }
}

//------------------------------------------------------------------------------------------
