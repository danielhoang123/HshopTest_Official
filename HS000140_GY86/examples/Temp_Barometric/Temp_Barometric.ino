#include "MS5611.h"

MS5611 MS5611(0x77);

#ifndef LED_BUILTIN
#define LED_BUILTIN    13
#endif

uint32_t start, stop;


void setup()
{
  Serial.begin(9600);
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS5611_LIB_VERSION: ");
  Serial.println(MS5611_LIB_VERSION);

  if (MS5611.begin() == true)
  {
    Serial.println("MS5611 found.");
  }
  else
  {
    Serial.println("MS5611 not found. halt.");
    while (1)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
  }
  Serial.println();
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  MS5611.setOversampling(OSR_ULTRA_LOW);
  test();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  MS5611.setOversampling(OSR_LOW);
  test();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  MS5611.setOversampling(OSR_STANDARD);
  test();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  MS5611.setOversampling(OSR_HIGH);
  test();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  MS5611.setOversampling(OSR_ULTRA_HIGH);
  test();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println();
}


void test()
{
  start = micros();
  int result = MS5611.read();
  stop = micros();
  if (result != MS5611_READ_OK)
  {
    Serial.print("Error in read: ");
    Serial.println(result);
  }
  else
  {
    Serial.print("T:\t");
    Serial.print(MS5611.getTemperature(), 2);Serial.print("(°C)\t");
    Serial.print("\tP:\t");
    Serial.print(MS5611.getPressure(), 2); Serial.print("(millibar)\t");
    Serial.print("\tt:\t");
    Serial.print(stop - start);
    Serial.println();
  }
}
