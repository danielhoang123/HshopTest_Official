#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "HMC5883L.h"


MPU6050 accelgyro;
HMC5883L mag;

int16_t mx, my, mz;

#define LED_PIN 13
bool blinkState = false;

void setup() {
   
    Wire.begin();
    accelgyro.setI2CMasterModeEnabled(false);

    accelgyro.setI2CBypassEnabled(true) ;
    accelgyro.setSleepEnabled(false);

    Serial.begin(9600);
    mag.initialize();
    Serial.println(mag.testConnection() ? "HMC5883L connection successful" : "HMC5883L connection failed");

    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    
    mag.getHeading(&mx, &my, &mz);

    Serial.print("mag:\t");
    Serial.print(mx); Serial.print("\t");
    Serial.print(my); Serial.print("\t");
    Serial.print(mz); Serial.print("\t");
    
    // heading = 0 -> huong Bac
    float heading = atan2(my, mx);
    if(heading < 0)
      heading += 2 * M_PI;
    Serial.print("heading:\t");
    Serial.println(heading * 180/M_PI);

}
