//------------------------------------------------------------------------------------------
// 1602 text display
//------------------------------------------------------------------------------------------
CDisplay display;
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
#ifndef GRAPHICS_MODE

uint8_t CDisplay::CustomChars[][8] =
{
  {B01100,B10010,B10010,B01100,B00000,B00000,B00000,B00000}, // symbol "°"
  {B00000,B00100,B00100,B01010,B01010,B10001,B11111,B00000}, // symbol "⌂"
  {B01110,B11011,B10001,B10001,B10001,B10001,B10001,B11111}, // symbol "Battery"
  //{B00000,B01100,B00100,B01110,B11010,B10011,B00000,B00000}, // symbol "Fan 1"
  //{B00000,B11001,B01011,B01110,B00100,B00110,B00000,B00000}, // symbol "Fan 2"
  //{B00000,B00001,B00111,B11100,B10110,B00011,B00000,B00000}, // symbol "Fan 3"
  {B00000,B01100,B00101,B11111,B10100,B00110,B00000,B00000}, // symbol "Fan 1"
  {B00000,B00010,B11010,B00100,B01011,B01000,B00000,B00000}, // symbol "Fan 2"
  {B00000,B11001,B01011,B00100,B11010,B10011,B00000,B00000}, // symbol "Fan 3"
#ifdef RUSSIAN
  {B11110,B10000,B10000,B11110,B10001,B10001,B11110,B00000}, // symbol "Б"
  {B11111,B10001,B10000,B10000,B10000,B10000,B10000,B00000}, // symbol "Г"
  {B01111,B00101,B00101,B01001,B10001,B11111,B10001,B00000}, // symbol "Д"
  {B10101,B10101,B10101,B11111,B10101,B10101,B10101,B00000}, // symbol "Ж"
  {B01110,B10001,B00001,B00010,B00001,B10001,B01110,B00000}, // symbol "З"
  {B10001,B10011,B10011,B10101,B11001,B11001,B10001,B00000}, // symbol "И"
  {B01110,B00000,B10001,B10011,B10101,B11001,B10001,B00000}, // symbol "Й"
  {B00011,B00111,B00101,B00101,B01101,B01001,B11001,B00000}, // symbol "Л"
  {B11111,B10001,B10001,B10001,B10001,B10001,B10001,B00000}, // symbol "П"
  {B10001,B10001,B10001,B01010,B00100,B01000,B10000,B00000}, // symbol "У"
  {B00100,B11111,B10101,B10101,B11111,B00100,B00100,B00000}, // symbol "Ф"
  {B10010,B10010,B10010,B10010,B10010,B10010,B11111,B00001}, // symbol "Ц"
  {B10001,B10001,B10001,B01111,B00001,B00001,B00001,B00000}, // symbol "Ч"
  {B10101,B10101,B10101,B10101,B10101,B10101,B11111,B00000}, // symbol "Ш"
  {B10101,B10101,B10101,B10101,B10101,B10101,B11111,B00001}, // symbol "Щ"
  {B10000,B10000,B10000,B11110,B10001,B10001,B11110,B00000}, // symbol "Ь"
  {B10001,B10001,B10001,B11001,B10101,B10101,B11001,B00000}, // symbol "Ы"
  {B10010,B10101,B10101,B11101,B10101,B10101,B10010,B00000}, // symbol "Ю"
  {B01111,B10001,B10001,B01111,B00101,B01001,B10001,B00000}, // symbol "Я"
#endif
};

#endif // GRAPHICS_MODE

//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------
char mesBuffer [LINE_LENGTH+1];
char mesBuffer2[LINE_LENGTH+1];
//------------------------------------------------------------------------------------------

const char * LoadMessage(CTextMessageId n)
{
  strcpy_P(mesBuffer, (char*)pgm_read_word(&(mes_table[n])));
  mesBuffer[LINE_LENGTH] = 0; // protection
  return mesBuffer;
}

//------------------------------------------------------------------------------------------

const char * LoadMessage2(CTextMessageId n)
{
  strcpy_P(mesBuffer2, (char*)pgm_read_word(&(mes_table[n])));
  mesBuffer2[LINE_LENGTH] = 0; // protection
  return mesBuffer2;
}

//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------

void  CDisplay::SetTextMode()
{
#ifndef OLED_I2C
  lcd.command(0x08);        // off screen
  lcd.command(0x17);        // switch to text mode
  lcd.command(0x01);        // clean RAM
  lcd.command(0x04 | 0x08); // on screen
#endif
}

//------------------------------------------------------------------------------------------

void  CDisplay::SetGraphMode()
{
#ifndef OLED_I2C
  lcd.command(0x08);      // off screen
  lcd.command(0x1F);      // switch to graphics mode
  lcd.command(0x01);      // clean RAM
  lcd.command(0x08|0x04); // on screen
#endif
}

//------------------------------------------------------------------------------------------

void  CDisplay::Init()
{
  pinMode(LCD_DETECT_PIN, INPUT_PULLUP);
  delay(10);
  int v = analogRead(LCD_DETECT_PIN);
  isOLED = (v > 512);

#ifdef DEBUG
  Serial.print(F("Detecting display type: jumper read = "));
  Serial.print(v);
  if (isOLED)
    Serial.println(F(" (OLED)"));
  else
    Serial.println(F(" (LCD)"));

  Serial.print(F("Initializing display\n"));
#endif

#ifdef OLED_I2C
  lcd.init();
  lcd.begin(16, 2);
#else
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
#endif

  if (isOLED)
  {
    // Fix bugs with Winstar OLED initializtion
#ifdef GRAPHICS_MODE
    SetGraphMode();
#else
    SetTextMode();
#endif

    // Remove the "Contrast" menu item, because OLED display doesn't need it
    menu.HideNode(MENU_DISP_CONTRAST);
  }
  else
  {
    // LCD may have backlight brightness 0 (off)
    varDisplayBright.valueMin = 0;
  }

#ifdef DEBUG
  Serial.print(F("Loading custom chars\n"));
#endif

#ifndef GRAPHICS_MODE
  // Load custom characters: maximum 8!
  lcd.createChar((byte)DEG  [0], CustomChars[0]); // DEG,   code == 1
  lcd.createChar((byte)DELTA[0], CustomChars[1]); // DELTA, code == 2
  lcd.createChar((byte)BATT [0], CustomChars[2]); // BATT,  code == 3
  lcd.createChar((byte)FAN1 [0], CustomChars[3]); // FAN1,  code == 4
  lcd.createChar((byte)FAN2 [0], CustomChars[4]); // FAN2,  code == 5
  lcd.createChar((byte)FAN3 [0], CustomChars[5]); // FAN3,  code == 6
#endif

  PrintText(0, 0, LoadMessage(TXT_LOGO));
  PrintText(4, 1, LoadMessage(isOLED ? TXT_VER_OLED : TXT_VER_LCD));

#ifdef DEBUG
  Serial.print(F("Done\n"));
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
#ifdef GRAPHICS_MODE
  lastSaverTime = millis();
#endif
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

void  CDisplay::Clear()
{
  lcd.command(0x01); // clean RAM

  for (int i=0; i<2; ++i)
      memset(memLine[i], 0, 17);
}

//------------------------------------------------------------------------------------------

void  CDisplay::SetBrightAndContrast()
{
  // Update dimming brightness value (PWM duty)
  // Use gamma correction (power of 2) to make brightness change more natural for perception
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

  uint32_t t = millis();

#ifdef GRAPHICS_MODE
  // Screensaver for graphics Winstar OLDE
  if (!isOff && (t > lastSaverTime + OLED_SCREEN_SAVER))
  {
      lastSaverTime = t;
      saverShiftX = random(4);
      saverShiftY = random(2);
      Clear();

#ifdef DEBUG
      sprintf(text, "Saver x = %i, y = %i", saverShiftX, saverShiftY);
      Serial.println(text);
#endif
  }
#endif

  SetBrightAndContrast();

  if (menu.isDisplayTest())
    Test();
  else
  {
    // Print line 0
    strcpy(text, menu.GetLine0());
    AppendWithSpaces(text, LINE_LENGTH);
    PrintLineSmart(0, text);
  
    // Print line 1
    strcpy(text, menu.GetLine1());
    AppendWithSpaces(text, LINE_LENGTH);
    PrintLineSmart(1, text);
  }

  // Display timeout
  if (!isOff && (varDisplayTimeout.value > 0) && (t/1000 > lastOnTime + varDisplayTimeout.value))
    Off(isOLED);
}

//------------------------------------------------------------------------------------------

void  CDisplay::AppendWithSpaces(char * text, int len)
{
  bool endFound = false;
  for (int i=0; i<=len; ++i)
  {
    if (text[i] == 0) endFound = true;
    if (endFound)     text[i] = ' ';
  }
  text[len] = 0;
}

//------------------------------------------------------------------------------------------

void  CDisplay::SetGraphCursor(int x, int y)
{
  if (0 <= x && x <= 99)
    lcd.command(LCD_SETDDRAMADDR | x);
  if (0 <= y && y <= 1)
    lcd.command(LCD_SETCGRAMADDR | y);
}

//------------------------------------------------------------------------------------------

void  CDisplay::SetTextCursor(int x, int y)
{
#ifdef GRAPHICS_MODE
  SetGraphCursor(x * 6, y);
#else
  lcd.setCursor(x, y);
#endif
}

//------------------------------------------------------------------------------------------

int   CDisplay::GetCharIndex(uint8_t c)
{
  if (c == BAR[0]) return -2;
  if (c < 0x21 || c > 0x85) return -1;
  return c - 0x21;
}

//------------------------------------------------------------------------------------------

void  CDisplay::PrintChar(int x, int y, char c)
{
#ifdef GRAPHICS_MODE
  if (x < 0 || x > 99-6) return;

  uint8_t b;
  int xx = x;
  int ind = GetCharIndex(c);
  if (ind < 0)
  {
    // unprintable character or bar
    b = (ind == -1) ? 0 : 255;
    
    for (int col=0; col<6; ++col)
    {
      lcd.command(LCD_SETDDRAMADDR | xx);
      lcd.write(b);
      ++xx;
    }
  }
  else
  {
    // copy 5 columns from font
    for (int col=0; col<5; ++col)
    {
      lcd.command(LCD_SETDDRAMADDR | xx);
      b = pgm_read_byte(&Font[0] + ind * 5 + col);
      lcd.write(b);
      ++xx;
    }
    // zero out 6th column
    lcd.command(LCD_SETDDRAMADDR | xx);
    lcd.write((uint8_t)0);
  }
#endif
}

//------------------------------------------------------------------------------------------

void  CDisplay::PrintText(int x, int y, const char * text)
{
#ifdef GRAPHICS_MODE

  if (y < 0 || y > 2) return;
  lcd.command(LCD_SETCGRAMADDR | y);
  
  int xx = x * 6 + saverShiftX;
  int i = 0;

  while (text[i])
  {
    PrintChar(xx, y, text[i]);
    xx += 6;
    i++;
  }

#else

  lcd.setCursor(x, y);
  lcd.print(text);

#endif
}

//------------------------------------------------------------------------------------------

void  CDisplay::PrintLineSmart(int y, const char * text)
{
#ifdef GRAPHICS_MODE

  if (y < 0 || y > 2) return;
  lcd.command(LCD_SETCGRAMADDR | y);
  
  int xx = saverShiftX;
  int i = 0;

  while (text[i])
  {
    if (text[i] != memLine[y][i])
      PrintChar(saverShiftX + 6 * i, y, text[i]);
    i++;
  }

  memcpy(memLine[y], text, 16);

#else

  PrintText(0, y, text);

#endif
}

//------------------------------------------------------------------------------------------

void  CDisplay::Test()
{
/*#ifdef GRAPHICS_MODE

  SetGraphCursor(testPos % 100, (testPos / 100) % 2);
  lcd.write(testPos < 200 ? 255 : 0);
  if (testPos++ >= 400) testPos = 0;

#else*/

  PrintText(testPos % 16, (testPos / 16) % 2, testPos < 16*2 ? BAR : " ");
  if (testPos++ >= 16*4) testPos = 0;
}

//------------------------------------------------------------------------------------------
