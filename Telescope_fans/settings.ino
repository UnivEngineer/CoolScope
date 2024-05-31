//------------------------------------------------------------------------------------------
// Save/load settings to EEPROM, power loss detection
//------------------------------------------------------------------------------------------
CSettings settings;
//------------------------------------------------------------------------------------------
#define RESISTOR_TO_PWR     46.9f // 44.3f // power voltage measurement divider R1, kOhms
#define RESISTOR_TO_GND     20.1f // 17.9f // power voltage measurement divider R2, kOhms
#define ADC_TO_VOLTS        (5.0f / 1023.0f * (RESISTOR_TO_PWR + RESISTOR_TO_GND) / RESISTOR_TO_GND)
#define POWER_USB_VOLTS     5.0f  // power voltage, considered as powered by USB
//------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------
// Reads variables from EEPROM

void    CSettings::Init()
{
  pinMode(POWER_DETECT_PIN, INPUT);

#ifdef DEBUG
  Serial.println(F("Loading variables..."));
  char text2[128];
#endif

  int16_t v = 0;
  int  addr = 0;

  for (CVariable * var = CVariable::First; var != NULL; var = var->Next)
  {
    if (var->isValueAddress())
    {
      EEPROM.get(addr, var->address);
      addr += sizeof(var->address);

      #ifdef DEBUG
        sprintf(text, "addr = %i, EEPROM = ", addr);
        Serial.print(text);
        AddressToHexStr(var->address, text);
        Serial.println(text);
      #endif
    }
    else
    {
      EEPROM.get(addr, v);
      addr += sizeof(int16_t);
  
      // if value read from EEPROM is out of range, this is probably first run,
      // we must reset variable to default.
      if (!var->set(v))
        var->reset();
  
      #ifdef DEBUG
        sprintf(text2, "addr = %i, EEPROM = %i, var = %i", addr, v, var->value);
        Serial.println(text2);
      #endif
    }
  }
}

//------------------------------------------------------------------------------------------
// Writes variables to EEPROM

void    CSettings::Write()
{
#ifdef DEBUG
  Serial.println(F("Saving variables..."));
#endif

  int  addr = 0;

  for (CVariable * var = CVariable::First; var != NULL; var = var->Next)
  {
    if (var->isValueAddress())
    {
      EEPROM.put(addr, var->address);
      addr += sizeof(var->address);

      #ifdef DEBUG
        sprintf(text, "addr = %i, var = ", addr);
        Serial.print(text);
        AddressToHexStr(var->address, text);
        Serial.println(text);
      #endif
    }
    else
    {
      EEPROM.put(addr, var->value);
      addr += sizeof(var->value);
  
      #ifdef DEBUG
        sprintf(text, "addr = %i, var = %i", addr, var->value);
        Serial.println(text);
      #endif
    }
  }
}

//------------------------------------------------------------------------------------------
// Resets variables to defaults

void    CSettings::Reset()
{
#ifdef DEBUG
  Serial.println(F("Resetting variables..."));
#endif

  for (CVariable * var = CVariable::First; var != NULL; var = var->Next)
  {
    var->reset();

#ifdef DEBUG
    Serial.println(var->value);
#endif
  }
}

//------------------------------------------------------------------------------------------
// Writes variables to EEPROM if minimal time after last saving has passed

void    CSettings::Save()
{
  uint32_t t = millis();

  if (firstPowerLoss || (t - lastSaveTick > EEPROM_WRITE_WAIT_TIME))
  {
#ifdef DEBUG
      Serial.print(F("!!!! Power lost, saving variables !!!! V = "));
      Serial.println(voltage);
#endif
  
    Write();
    lastSaveTick = t;

    // Wait until last data chunck recorded to EEPROM
    delay(POWER_DETECT_PERIOD);

    // Indicate that data has been saved sucessfully with onboard LED
    digitalWrite(BOARD_LED_PIN, HIGH);
  }

  firstPowerLoss = false;
}

//------------------------------------------------------------------------------------------
// Returns true if power loss detected

bool    CSettings::DetectPowerLoss()
{
  // Measure 12V line voltage, convert to volts
  int v = analogRead(POWER_DETECT_PIN);
  voltage = (float)v * ADC_TO_VOLTS;

  voltageSum += voltage;

  // Detect power loss as a dropping of 12V line voltage.
  // Voltage threshold should be somewhat lower than the battery alarm setting.
  float powerLossVoltage = varBattAlarmVolt.getf() - 1.0f;
  powerLossVoltage = min(powerLossVoltage, 10.0f);

  // If voltage is < 5V, we are powering from USB, so don't
  // detect this as a power loss (USB debug mode).
  poweredByUSB = (voltage < POWER_USB_VOLTS);

  powerLostPrev = powerLost;
  powerLost = !poweredByUSB && (voltage < powerLossVoltage);

  // Delay before exit the power lost state
  uint32_t t = millis();
  if (powerLost)
    lastPowerLossTick = t;
  else if (t - lastPowerLossTick < POWER_RESTORE_DELAY)
    powerLost = true;

  return powerLost;
}

//------------------------------------------------------------------------------------------

bool    CSettings::isLowBattery()
{
  return (varLowBattAlarm.value == 1) && !poweredByUSB && (voltageAvg < varBattAlarmVolt.getf());
}

//------------------------------------------------------------------------------------------

void    CSettings::Update(int NumCycles)
{
  voltageAvg = voltageSum / NumCycles;
  voltageSum = 0.0f;

//#ifdef DEBUG
//      Serial.print(F("Power voltage = "));
//      Serial.println(voltageAvg);
//#endif

  // Switch off onboard LED if it was turned on
  if (digitalRead(BOARD_LED_PIN) == HIGH)
    digitalWrite(BOARD_LED_PIN, LOW);

  // Show mssage if battery is low
  if (isLowBattery())
  {
    menu.ShowMessage(
      LoadMessage(TXT_LOW_BATTERY),
      GetVoltageStr(),
      MSG_SHORT_TIME,
      true);
  }
}

//------------------------------------------------------------------------------------------
