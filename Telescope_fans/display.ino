//------------------------------------------------------------------------------------------
// 1602 text display
//------------------------------------------------------------------------------------------
CDisplay display;
//------------------------------------------------------------------------------------------
char mesBuffer[17];
//------------------------------------------------------------------------------------------

const char * LoadMessage(CTextMessageId n)
{
  strcpy_P(mesBuffer, (char*)pgm_read_word(&(mes_table[n])));
  mesBuffer[16] = 0; // protection
  return mesBuffer;
}

//------------------------------------------------------------------------------------------

uint8_t CDisplay::CustomChars[CDisplay::NCustomChars][8] =
{
  {B11110,B10000,B10000,B11110,B10001,B10001,B11110,B00000}, // index  0, symbol "Б"
  {B11111,B10001,B10000,B10000,B10000,B10000,B10000,B00000}, // index  1, symbol "Г"
  {B01111,B00101,B00101,B01001,B10001,B11111,B10001,B00000}, // index  2, symbol "Д"
  {B10101,B10101,B10101,B11111,B10101,B10101,B10101,B00000}, // index  3, symbol "Ж"
  {B01110,B10001,B00001,B00010,B00001,B10001,B01110,B00000}, // index  4, symbol "З"
  {B10001,B10011,B10011,B10101,B11001,B11001,B10001,B00000}, // index  5, symbol "И"
  {B01110,B00000,B10001,B10011,B10101,B11001,B10001,B00000}, // index  6, symbol "Й"
  {B00011,B00111,B00101,B00101,B01101,B01001,B11001,B00000}, // index  7, symbol "Л"
  {B11111,B10001,B10001,B10001,B10001,B10001,B10001,B00000}, // index  8, symbol "П"
  {B10001,B10001,B10001,B01010,B00100,B01000,B10000,B00000}, // index  9, symbol "У"
  {B00100,B11111,B10101,B10101,B11111,B00100,B00100,B00000}, // index 10, symbol "Ф"
  {B10010,B10010,B10010,B10010,B10010,B10010,B11111,B00001}, // index 11, symbol "Ц"
  {B10001,B10001,B10001,B01111,B00001,B00001,B00001,B00000}, // index 12, symbol "Ч"
  {B10101,B10101,B10101,B10101,B10101,B10101,B11111,B00000}, // index 13, symbol "Ш"
  {B10101,B10101,B10101,B10101,B10101,B10101,B11111,B00001}, // index 14, symbol "Щ"
  {B10000,B10000,B10000,B11110,B10001,B10001,B11110,B00000}, // index 15, symbol "Ь"
  {B10001,B10001,B10001,B11001,B10101,B10101,B11001,B00000}, // index 16, symbol "Ы"
  {B10010,B10101,B10101,B11101,B10101,B10101,B10010,B00000}, // index 17, symbol "Ю"
  {B01111,B10001,B10001,B01111,B00101,B01001,B10001,B00000}, // index 18, symbol "Я"
  {B01100,B10010,B10010,B01100,B00000,B00000,B00000,B00000}, // index 19, symbol "°"
  {B00000,B00100,B00100,B01010,B01010,B10001,B11111,B00000}, // index 20, symbol "⌂"
};

//------------------------------------------------------------------------------------------

void  CDisplay::SetTextMode()
{
  lcd.command(0x08);        // off screen
  lcd.command(0x17);        // switch to text mode
  lcd.command(0x01);        // clean RAM
  lcd.command(0x04 | 0x08); // on screen
}

//------------------------------------------------------------------------------------------

void  CDisplay::SetGraphMode()
{
  lcd.command(0x08);      // off screen
  lcd.command(0x1F);      // switch to graphics mode
  lcd.command(0x01);      // clean RAM
  lcd.command(0x08|0x04); // on screen
}

//------------------------------------------------------------------------------------------

void  CDisplay::Init()
{
  pinMode(LCD_DETECT_PIN, INPUT_PULLUP);
  delay(10);
  int v = analogRead(LCD_DETECT_PIN);
  isOLED = (v > 512);

  #ifdef DEBUG
    Serial.print(F("Detecting disply type: jumper read = "));
    Serial.print(v);
    if (isOLED)
      Serial.println(F(" (OLED)"));
    else
      Serial.println(F(": (LCD)"));
  #endif

  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  if (isOLED)
  {
    // Fix bugs with Winstar OLED initializtion
    SetTextMode();

    // Remove "Contrast" menu item, because OLED display doesn't need it
    menu.HideNode(MENU_DISP_CONTRAST);
  }
  else
  {
    // LCD may have backlight brightness 0 (off)
    varDisplayBright.valueMin = 0;
  }

  // Load custom characters: maximum 8!
  lcd.createChar((byte)DEG  [0], CustomChars[19]); // DEG   code == 1
  lcd.createChar((byte)DELTA[0], CustomChars[20]); // DELTA code == 2

#ifdef RUSSIAN
  lcd.createChar(3, CustomChars[4]);
  lcd.createChar(4, CustomChars[1]);
  lcd.createChar(5, CustomChars[9]);

  lcd.setCursor(0, 0);
  lcd.print(F(\0x03 "A" \0x04 "P" \0x05 \0x03 "KA..."));
#else
  lcd.setCursor(0, 0);
  lcd.print  (F("-= COOL SCOPE =-"));
  lcd.setCursor(0, 1);
  if (isOLED)
    lcd.print(F("   v1.0 OLED"));
  else
    lcd.print(F("   v1.0 LCD"));
#endif

  // Set display contrast/brightness (variables must be already initialized from EEPROM)
  SetBrightAndContrast();
}

//------------------------------------------------------------------------------------------

void  CDisplay::Touch()
{
  isOff = false;
  lastOnTime = millis() / 1000;
}

//------------------------------------------------------------------------------------------

void  CDisplay::On()
{
  lcd.display();
  Touch();
}

//------------------------------------------------------------------------------------------

void  CDisplay::Off(bool hard)
{
  if (hard)
    lcd.noDisplay();

  analogWrite(PWM_BRIGHT_LCD, 0); // turn off backlight

  isOff = true;
}

//------------------------------------------------------------------------------------------

void  CDisplay::SetBrightAndContrast()
{
  // Update dimming brightness value (PWM duty)
  // Use gamma correction (power of 2) to make brightness change more linear to eye
  const uint32_t brMaxSquared = varDisplayBright.valueMax * varDisplayBright.valueMax;
  uint32_t brSquared = varDisplayBright.value * varDisplayBright.value;

  // Set display brightness/contrast PWM duty
  if (isOLED)
  {
    // Winstar OLED module doesn't have backlight LED, and pin 3 is used for brightness dimming
    uint32_t brightDuty = MaxBrightDutyOLED - (brSquared * MaxBrightDutyOLED) / brMaxSquared;
    analogWrite(PWM_CONTRAST_LCD, brightDuty); // inverted
  }
  else
  {
    uint32_t brightDuty = isOff ? 0 : MinBrightDutyLCD + (MaxBrightDutyLCD - MinBrightDutyLCD) * brSquared / brMaxSquared;
    analogWrite(PWM_BRIGHT_LCD, brightDuty);

    const uint32_t cnMaxSquared = varDisplayContr.valueMax;
    uint32_t cnSquared = varDisplayContr.value;
    uint32_t contrDuty = MinContrDutyLCD + (MaxContrDutyLCD - MinContrDutyLCD) * cnSquared / cnMaxSquared;
    analogWrite(PWM_CONTRAST_LCD, 255 - contrDuty);
  }
}

//------------------------------------------------------------------------------------------

void  CDisplay::Update()
{
  if (isOLED && isOff && (varDisplayTimeout.value > 0)) return;

  SetBrightAndContrast();

  // Print line 0
  strcpy(text, menu.GetLine0());
  AppendWithSpaces(text, LINE_LENGTH);
  lcd.setCursor(0, 0);
  lcd.print(text);

  // Print line 1
  strcpy(text, menu.GetLine1());
  AppendWithSpaces(text, LINE_LENGTH);
  lcd.setCursor(0, 1);
  lcd.print(text);

  // Display timeout
  if (!isOff && (varDisplayTimeout.value > 0) && (millis() / 1000 > lastOnTime + varDisplayTimeout.value))
    Off(isOLED);
}

//------------------------------------------------------------------------------------------

void  CDisplay::AppendWithSpaces(char * text, int len)
{
  bool endFound = false;
  for (int i=0; i<len; ++i)
  {
    if (text[i] == 0) endFound = true;
    if (endFound)     text[i] = ' ';
  }
  text[len] = 0;
}

//------------------------------------------------------------------------------------------
