#ifndef LOCALE_H
#define LOCALE_H
//------------------------------------------------------------------------------------------
// Special characters
//------------------------------------------------------------------------------------------
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
  TXT_POS_PRESSURE,
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
  TXT_FANS_DISABLED,
  TXT_ON,
  TXT_OFF,
  TXT_DISPLAY_LANGUAGE,
  TXT_LANGUAGE_ENG,
  TXT_LANGUAGE_RUS
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
const char mes11[] PROGMEM = "(C)SpaceEngineer";
const char mes12[] PROGMEM = "Mode once cooled";
const char mes13[] PROGMEM = "Target " DELTA "T";
const char mes14[] PROGMEM = "Cooling speed";
const char mes15[] PROGMEM = "Keeping speed";
const char mes16[] PROGMEM = "Pos. pressure";
const char mes17[] PROGMEM = "Brightness";
const char mes18[] PROGMEM = "Contrast";
const char mes19[] PROGMEM = "Timeout";
const char mes20[] PROGMEM = "Fan stuck alarm";
const char mes21[] PROGMEM = "Uptime";            // "Time since start";
const char mes22[] PROGMEM = "Power voltage";
const char mes23[] PROGMEM = "About";
const char mes24[] PROGMEM = "Sensors";
const char mes25[] PROGMEM = "Target " DELTA "T pair";
const char mes26[] PROGMEM = "Assign sensors";
const char mes27[] PROGMEM = "Mirror";
const char mes28[] PROGMEM = "Tube";
const char mes29[] PROGMEM = "Ambient";
const char mes30[] PROGMEM = "External";
const char mes31[] PROGMEM = "Mirror & tube";
const char mes32[] PROGMEM = "Mirror & ambient";
const char mes33[] PROGMEM = "Mirror & extrnal";
const char mes34[] PROGMEM = "< Not assigned >";
const char mes35[] PROGMEM = "Error";
const char mes36[] PROGMEM = "-= COOL SCOPE =-";
const char mes37[] PROGMEM = VERSION " OLED";
const char mes38[] PROGMEM = VERSION " LCD";
const char mes39[] PROGMEM = "Test";
const char mes40[] PROGMEM = "Powered by USB";
const char mes41[] PROGMEM = "Low batt. alarm";
const char mes42[] PROGMEM = "Batt. alarm volt";
const char mes43[] PROGMEM = "Battery is low!";
const char mes44[] PROGMEM = "Fans enabled";
const char mes45[] PROGMEM = "Fans disabled";
const char mes46[] PROGMEM = "On";
const char mes47[] PROGMEM = "Off";
const char mes48[] PROGMEM = "Language";
const char mes49[] PROGMEM = "English";
const char mes50[] PROGMEM = "Russian";

// Second language, win-1251

#ifdef BI_LANG
const char mer00[] PROGMEM = "\315\340\361\362\360\356\351\352\350";                            // "Настройки";
const char mer01[] PROGMEM = "\316\365\353\340\346\344\345\355\350\345";                        // "Охлаждение";
const char mer02[] PROGMEM = "\304\350\361\357\353\345\351";                                    // "Дисплей";
const char mer03[] PROGMEM = "\310\355\364\356\360\354\340\366\350\377";                        // "Информация";
const char mer04[] PROGMEM = "\317\345\360\345\344\355\350\351 \342\345\355\362!";              // "Передний вент!";
const char mer05[] PROGMEM = "  \307\340\344\355\350\351 \342\345\355\362!";                    // "  Задний вент!";
const char mer06[] PROGMEM = "\304\345\360\346\340\362\374 " DELTA "T";                         // "Держать " DELTA "T";
const char mer07[] PROGMEM = "\317\360\356\344. \355\340\343\355\345\362\340\362\374";          // "Прод. нагнетать";
const char mer08[] PROGMEM = "\317\360\356\344. \342\373\362\377\343\350\342\340\362\374";      // "Прод. вытягивать";
const char mer09[] PROGMEM = "\316\361\362\340\355\356\342\350\362\374";                        // "Остановить";
const char mer10[] PROGMEM = "\316\365\353\340\346\344\345\355\350\345 \342\373\352\353";       // "Охлаждение выкл";
const char mer11[] PROGMEM = "(C)SpaceEngineer";                                                // "(C)SpaceEnigneer";
const char mer12[] PROGMEM = "\317\356\361\353\345 \356\365\353\340\346\344\345\355\350\377";   // "После охлаждения";
const char mer13[] PROGMEM = "\326\345\353\345\342\356\345 " DELTA "T";                         // "Целевое " DELTA "T";
const char mer14[] PROGMEM = "\321\352\356\360\356\361\362\374 \356\365\353\340\346\344.";      // "Скорость охлажд.";
const char mer15[] PROGMEM = "\321\352\356\360\356\361\362\374 \357\356\344\344\345\360\346";   // "Скорость поддерж";
const char mer16[] PROGMEM = "\317\356\347. \344\340\342\353\345\355\350\345";                  // "Поз. давление"
const char mer17[] PROGMEM = "\337\360\352\356\361\362\374";                                    // "Яркость";
const char mer18[] PROGMEM = "\312\356\355\362\360\340\361\362";                                // "Контраст";
const char mer19[] PROGMEM = "\322\340\351\354\340\363\362";                                    // "Таймаут";
const char mer20[] PROGMEM = "\317\360\345\344\363\357\360. \342\345\355\362\350\353.";         // "Предупр. вентил.";
const char mer21[] PROGMEM = "\300\357\362\340\351\354";                                        // "Аптайм";
const char mer22[] PROGMEM = "\315\340\357\360\377\346\345\355\350\345 \357\350\362.";          // "Напряжение пит.";
const char mer23[] PROGMEM = "\316 \360\340\347\360\340\341\356\362\367\350\352\345";           // "О разработчике";
const char mer24[] PROGMEM = "\321\345\355\361\356\360\373";                                    // "Сенсоры";
const char mer25[] PROGMEM = "\317\340\360\340 \366\345\353\345\342. " DELTA "T";               // "Пара целев. " DELTA "T";
const char mer26[] PROGMEM = "\315\340\347\355\340\367\350\362\374 \361\345\355\361\356\360";   // "Назначить сенсор";
const char mer27[] PROGMEM = "\307\345\360\352\340\353\356";                                    // "Зеркало";
const char mer28[] PROGMEM = "\322\360\363\341\340";                                            // "Труба";
const char mer29[] PROGMEM = "\316\352\360\363\346\345\355\350\345";                            // "Окружение";
const char mer30[] PROGMEM = "\302\355\345\370\355\350\351";                                    // "Внешний";
const char mer31[] PROGMEM = "\307\345\360\352\340\353\356 \350 \362\360\363\341\340";          // "Зеркало и труба";
const char mer32[] PROGMEM = "\307\345\360\352\340\353\356 \350 \356\352\360\363\346.";         // "Зеркало и окруж.";
const char mer33[] PROGMEM = "\307\345\360\352\340\353\356 \350 \342\355\345\370\355.";         // "Зеркало и внешн.";
const char mer34[] PROGMEM = "< \315\345 \355\340\347\355\340\367\345\355\356 >";               // "< Не назначено >";
const char mer35[] PROGMEM = "\316\370\350\341\352\340";                                        // "Ошибка";
const char mer36[] PROGMEM = "-= COOL SCOPE =-";                                                // "-= COOL SCOPE =-";
const char mer37[] PROGMEM = VERSION " OLED";                                                   // "v1.x OLED";
const char mer38[] PROGMEM = VERSION " LCD";                                                    // "v1.x LCD";
const char mer39[] PROGMEM = "\322\345\361\362";                                                // "Тест";
const char mer40[] PROGMEM = "\317\350\362\340\355\350\345 \357\356 USB";                       // "Питание по USB";
const char mer41[] PROGMEM = "\317\360\345\344\363\357\360. \341\340\362\340\360\345\350";      // "Предупр. батареи";
const char mer42[] PROGMEM = "\315\340\357\360\377\346. \357\360\345\344\363\357\360.";         // "Напряж. предупр.";
const char mer43[] PROGMEM = "\301\340\362\340\360\345\377 \361\340\344\350\362\361\377!";      // "Батарея садится!";
const char mer44[] PROGMEM = "\302\345\355\362. \342\352\353\376\367\345\355\373";              // "Вент. включены";
const char mer45[] PROGMEM = "\302\345\355\362. \342\373\352\353\376\367\345\355\373";          // "Вент. выключены";
const char mer46[] PROGMEM = "\302\352\353";                                                    // "Вкл"
const char mer47[] PROGMEM = "\302\373\352\353";                                                // "Выкл"
const char mer48[] PROGMEM = "\337\347\373\352";                                                // "Язык";
const char mer49[] PROGMEM = "\300\355\343\353\350\351\361\352\350\351";                        // "Английский";
const char mer50[] PROGMEM = "\320\363\361\361\352\350\351";                                    // "Русский";
#endif

//------------------------------------------------------------------------------------------

const char * const mes_table[] PROGMEM =
{
  mes00, mes01, mes02, mes03, mes04, mes05, mes06, mes07, mes08, mes09,
  mes10, mes11, mes12, mes13, mes14, mes15, mes16, mes17, mes18, mes19,
  mes20, mes21, mes22, mes23, mes24, mes25, mes26, mes27, mes28, mes29,
  mes30, mes31, mes32, mes33, mes34, mes35, mes36, mes37, mes38, mes39,
  mes40, mes41, mes42, mes43, mes44, mes45, mes46, mes47, mes48, mes49,
  mes50
};

#ifdef BI_LANG
const char * const mer_table[] PROGMEM =
{
  mer00, mer01, mer02, mer03, mer04, mer05, mer06, mer07, mer08, mer09,
  mer10, mer11, mer12, mer13, mer14, mer15, mer16, mer17, mer18, mer19,
  mer20, mer21, mer22, mer23, mer24, mer25, mer26, mer27, mer28, mer29,
  mer30, mer31, mer32, mer33, mer34, mer35, mer36, mer37, mer38, mer39,
  mer40, mer41, mer42, mer43, mer44, mer45, mer46, mer47, mer48, mer49,
  mer50
};
#endif

//------------------------------------------------------------------------------------------
const char * LoadMessage (CTextMessageId n);
const char * LoadMessage2(CTextMessageId n);
//------------------------------------------------------------------------------------------
#endif // LOCALE_H
