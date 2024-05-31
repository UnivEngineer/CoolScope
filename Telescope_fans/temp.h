#ifndef TEMP_H
#define TEMP_H
//------------------------------------------------------------------------------------------
// Temperature sensors
//------------------------------------------------------------------------------------------
// DS18B20 sensor
#include <OneWire.h>
//------------------------------------------------------------------------------------------
// DHT sensor
#ifdef USE_DHT
#include <DHT.h>
#include <DHT_U.h>
#endif
//------------------------------------------------------------------------------------------

enum  ESensorName
{
  S_MIRROR = 0, // mirror sensor
  S_TUBE,       // inside tube sensor
  S_AMBIENT,    // ambient (air) sensor in the cooler controller
  S_EXTERNAL,   // external sensor connected by wire
  S_COUNT
};

//------------------------------------------------------------------------------------------
#define ADDR_SIZE 8
#define NO_TEMP -1000.0f
//------------------------------------------------------------------------------------------

class CTempSensors
{
public:

  byte    AddressDetected[S_COUNT][8];

private:

  OneWire ds;

  #ifdef USE_DHT
  DHT dht(DHT_PIN, DHT11); // Constants: DHT11, DHT22, DHT21
  #endif

  uint32_t lastTempReadTime = 0;

public:

  CTempSensors();

  void  Init();
  void  Update();

  void  GetNextAddress(byte * addr);
  void  GetPrevAddress(byte * addr);

  bool  isAddressValid(byte * addr);

private:

  float ReadTempSensor(byte * addr);
  bool  isAddressEqual(byte * addr1, byte * addr2);
  void  AssignNoAddress(byte * addr);
};

//------------------------------------------------------------------------------------------
extern CTempSensors temp;
//------------------------------------------------------------------------------------------
#endif // TEMP_H
