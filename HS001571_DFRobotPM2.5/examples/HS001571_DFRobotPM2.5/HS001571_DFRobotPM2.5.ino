#include "DFRobot_AirQualitySensor.h"

#define I2C_ADDRESS    0x19
  DFRobot_AirQualitySensor particle(&Wire ,I2C_ADDRESS);

void setup() {
  Serial.begin(115200);
/**
  Sensor initialization is used to initialize IIC, which is determined by the communication mode used at this time.
*/
  while(!particle.begin())
  {
    Serial.println("NO Deivces !");
    delay(1000);
  }
  Serial.println("sensor begin success!");
  delay(1000);
/**
  Get sensor version number
*/
  uint8_t version = particle.gainVersion();
  Serial.print("version is : ");
  Serial.println(version);
  delay(1000);
}

void loop() {
/**
 *@brief : Get concentration of PM1.0 PM2.5 PM10
 *@param :PARTICLE_PM1_0_STANDARD  Standard particle  
          PARTICLE_PM2_5_STANDARD  Standard particle  
          PARTICLE_PM10_STANDARD   Standard particle 
          PARTICLE_PM1_0_ATMOSPHERE  In atmospheric environment
          PARTICLE_PM2_5_ATMOSPHERE  In atmospheric environment
          PARTICLE_PM10_ATMOSPHERE   In atmospheric environment
*/  
  uint16_t PM2_5 = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_STANDARD);
  uint16_t PM1_0 = particle.gainParticleConcentration_ugm3(PARTICLE_PM1_0_STANDARD);
  uint16_t PM10 = particle.gainParticleConcentration_ugm3(PARTICLE_PM10_STANDARD);
  Serial.print("PM2.5 concentration:");
  Serial.print(PM2_5);
  Serial.println(" ug/m3");
  Serial.print("PM1.0 concentration:");
  Serial.print(PM1_0);
  Serial.println(" ug/m3");
  Serial.print("PM10 concentration:");
  Serial.print(PM10);
  Serial.println(" ug/m3");
  Serial.println();
  delay(1000);
}
