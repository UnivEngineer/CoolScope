//------------------------------------------------------------------------------------------
// Temperature sensors
//------------------------------------------------------------------------------------------
CTempSensors temp;
//------------------------------------------------------------------------------------------

CTempSensors::CTempSensors():
ds(DS18B20_PIN)
{
};

//------------------------------------------------------------------------------------------

void  CTempSensors::Init()
{
  Update();

#ifdef USE_DHT
  // Enable input for DHT sensor
  pinMode(DHT_PIN, INPUT_PULLUP); // enable pull-up resistor

  // Note that older versions of this library took an optional third parameter to
  // tweak the timings for faster processors.  This parameter is no longer needed
  // as the current DHT reading algorithm adjusts itself to work on faster procs.
  dht.begin();
#endif

  // Wait for first temperature values
  delay(TEMP_SENSOR_READ_PERIOD);
}

//------------------------------------------------------------------------------------------

void  CTempSensors::Update()
{
  uint32_t t = millis();
  if (t - lastTempReadTime >= TEMP_SENSOR_READ_PERIOD)
  {
#ifdef USE_DHT
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    state.humidity  = dht.readHumidity();
    state.tempBoard = dht.readTemperature();
#endif

    state.temp[S_MIRROR]   = ReadTempSensor(varSensor0Index.address);
    state.temp[S_TUBE]     = ReadTempSensor(varSensor1Index.address);
    state.temp[S_AMBIENT]  = ReadTempSensor(varSensor2Index.address);
    state.temp[S_EXTERNAL] = ReadTempSensor(varSensor3Index.address);

    state.CalcTempDelta();

    lastTempReadTime = t;
  }
}

//------------------------------------------------------------------------------------------

bool  CTempSensors::isAddressEqual(byte * addr1, byte * addr2)
{
  for (int i=0; i<8; ++i)
  {
    if (addr1[i] != addr2[i])
      return false;
  }
  return true;
}

//------------------------------------------------------------------------------------------

bool  CTempSensors::isAddressValid(byte * addr)
{
  if ((addr[0] != 0x10) && (addr[0] != 0x28)) return false;
  return OneWire::crc8(addr, 7) == addr[7];
}

//------------------------------------------------------------------------------------------

void  CTempSensors::GetNextAddress(byte * addr)
{
  #ifdef DEBUG
    Serial.print(F("Detecting NEXT address for "));
    AddressToHexStr(addr, text);
    Serial.println(text);
  #endif

  bool empty = !isAddressValid(addr);

  int  index = 0;
  int  nextIndex = -1000;
  byte b[8];
  memset(b, 0, sizeof(b));

  while (ds.search(b))
  {
    #ifdef DEBUG
      Serial.print(F("index = "));
      Serial.print(index);
      Serial.print(F(", address = "));
      AddressToHexStr(b, text);
      Serial.println(text);

      if (!isAddressValid(b))
          Serial.println(F("invalid address or CRC"));
    #endif

    if (empty)
      nextIndex = index;

    if (index == nextIndex)
      break;

    if (isAddressEqual(addr, b))
      nextIndex = index + 1;

    ++index;
  }

  #ifdef DEBUG
    if ((nextIndex >= 0) && (nextIndex < S_COUNT))
    {
      Serial.print(F("Done. Next index = "));
      Serial.println(nextIndex);
    }
    else
      Serial.println(F("Done. Next index is NOT FOUND"));
  #endif

  ds.reset_search();

  if ((nextIndex >= 0) && (nextIndex < S_COUNT))
    memcpy(addr, b, sizeof(b));
}

//------------------------------------------------------------------------------------------

void  CTempSensors::GetPrevAddress(byte * addr)
{
  #ifdef DEBUG
    Serial.print(F("Detecting PREV address for "));
    AddressToHexStr(addr, text);
    Serial.println(text);
  #endif

  bool empty = !isAddressValid(addr);
  if (empty) return;

  int  index = 0;
  int  prevIndex = -1000;
  byte b[8], m[8];
  memset(b, 0, sizeof(b));
  memset(m, 0, sizeof(m));

  while (ds.search(b))
  {
    #ifdef DEBUG
      Serial.print(F("index = "));
      Serial.print(index);
      Serial.print(F(", address = "));
      AddressToHexStr(b, text);
      Serial.println(text);

      if (!isAddressValid(b))
          Serial.println(F("invalid address or CRC"));
    #endif

    if (isAddressEqual(addr, b))
    {
      prevIndex = index - 1;
      break;
    }

    memcpy(m, b, sizeof(b));

    ++index;
  }

  #ifdef DEBUG
    if ((prevIndex >= 0) && (prevIndex < S_COUNT))
    {
      Serial.print(F("Done. Prev index = "));
      Serial.println(prevIndex);
    }
    else
      Serial.println(F("Done. Prev index is NOT FOUND"));
  #endif

  ds.reset_search();

  if (prevIndex == -1)
    memset(addr, 0xff, sizeof(m));  // assign "non assigned" value

  if ((prevIndex >= 0) && (prevIndex < S_COUNT))
    memcpy(addr, m, sizeof(m));
}

//------------------------------------------------------------------------------------------
// Returns the temperature from one DS18S20 in °C

float CTempSensors::ReadTempSensor(byte * addr)
{
  if (!isAddressValid(addr))
  {
    /*#ifdef DEBUG
      AddressToHexStr(addr, text);
      Serial.print(F("Device "));
      Serial.print(text);
      Serial.println(F(": invalid address or CRC"));
    #endif*/
    return NO_TEMP;
  }
  
  // Read temperature from PREVIOUS conversion command

  byte present = ds.reset();
  ds.select(addr);  
  ds.write(0xBE); // Read the scratchpad

  byte data[12];
  for (int i=0; i<9; i++) // we need 9 bytes
    data[i] = ds.read();

  byte dataCRC = OneWire::crc8(data, 8);
  if (dataCRC != data[8])
  {
    #ifdef DEBUG
      AddressToHexStr(addr, text);
      Serial.print(F("Device "));
      Serial.print(text);
      Serial.print(F(": invalid data CRC (computed = "));
      Serial.print(dataCRC);
      Serial.print(F(", read = "));
      Serial.print(data[8]);
      Serial.println(")");
    #endif
    return NO_TEMP;
  }

  // Get the sensor resolution: 9 bits (0), 10 bits (1), 11 bits (2), 12 bits (3)
  // If the resolution is not 12 bits, lower bits of LB (data[0]) are undefined,
  // so better to zero them out
  byte res = (data[4] >> 5) & 0x03;
  data[0] = data[0] & ((byte)(0xFF << (0x03 - res)));

  // Top 5 bits of MS (data[1]) byte are sign, we must leave onle one sign bit.
  // Do this by leftwise shifing of everything by 4 bits. So high byte (MS) is
  // shifted by 4 + 8 bits, and the low byte (LS) is shifted by 4.
  int16_t t = ((int16_t)data[1] << 12) | ((int16_t)data[0] << 4);

  // t is in units of 1/16 if °C, so we must divide by 16. But we did
  // a 4 bit leftwise shift, so we must divide by 16*16 = 256.
  float f = (float)t * 0.00390625f;

  /*if (index == 0)
  {
    sprintf(text, "res = %i, %x %x, %x (%i), %f", res, data[1], data[0], t, t, f);
    Serial.println(text);
  }*/

  // Start new conversion
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 0); // start conversion, with parasite power OFF on at the end
  //ds.write(0x44, 1); // start conversion, with parasite power ON on at the end

  return f;
}

//------------------------------------------------------------------------------------------
