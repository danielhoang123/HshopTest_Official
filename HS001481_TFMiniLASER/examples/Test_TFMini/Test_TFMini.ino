/*
  * @File  : DFRobot_TFmini_test.ino
  * @Brief : This example use TFmini to measure distance
  *         With initialization completed, we can get distance value and signal strength
  * @Copyright   [DFRobot](https://www.dfrobot.com), 2016
  *             GNU Lesser General Public License
  *
  * @version  V1.0
  * @date  2018-1-10
  * 
  * Code test cho TF Mini Laser
  * Red   ------------- 5VDC
  * Black ------------- GND
  * White ------------- 13
  * Green ------------- 12
*/

#include <DFRobot_TFmini.h>

SoftwareSerial mySerial(12, 13); // RX, TX

DFRobot_TFmini  TFmini;
uint16_t distance,strength;

void setup(){
    Serial.begin(115200);
    TFmini.begin(mySerial);
}

void loop(){
    if(TFmini.measure()){                      //Measure Distance and get signal strength
        distance = TFmini.getDistance();       //Get distance data
        strength = TFmini.getStrength();       //Get signal strength data
        Serial.print("Distance = ");
        Serial.print(distance);
        Serial.println("cm");
        Serial.print("Strength = ");
        Serial.println(strength);
        delay(500);
    }
    delay(500);
}
