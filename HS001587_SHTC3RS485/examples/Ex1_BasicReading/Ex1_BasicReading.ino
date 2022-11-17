#include "SHTC3Modbus.h"

#define SHT_RX 10
#define SHT_TX 11

SHTC3 sht(SHT_RX,SHT_TX, BAUD_4800, 0x01);

void FactoryReset(){

  sht.setBaudrate(4800);
  delay(10);
  if(sht.readAddress() != 1){
    sht.setAddress(1);
    delay(10);
  }
  
  if(sht.readAddress() == 1 && sht.readBaudrate() == 4800){
    Serial.println("Your sensor has been setup to default setting: Address(0x01) & Baudrate(4800)");
    delay(10);
  } 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("Start reading SHTC3 Modbus (HSHOP)"));
  //Serial.println("Config sensor...");
  delay(500);

  sht.begin(4800);
  if(sht.readAddress() != 0){
    Serial.print("Sensor's baudrate is: 4800 and device's address is: 0x");
    Serial.print(sht.readAddress(), HEX);
    Serial.println("");
    delay(10);
    sht.setAddress(1);
    delay(1000);
  }else{
    Serial.println("Sensor's baudrate is not 4800");
    sht.begin(2400);
    delay(10);
    if(sht.readAddress() != 0){
      Serial.print("Sensor's baudrate is: 2400 and device's address is: 0x");
      Serial.print(sht.readAddress(), HEX);
      Serial.println("");
      delay(1000);

      sht.setAddress(1);
      delay(20);
      sht.setBaudrate(4800);
      delay(20);
      sht.begin(4800);
      delay(20);

    }else{
      Serial.println("Sensor's baudrate is not 2400");
      sht.begin(9600);
      delay(10);
      if(sht.readAddress() != 0){

        Serial.print("Sensor's baudrate is: 9600 and device's address is: 0x");
        Serial.print(sht.readAddress(), HEX);
        Serial.println("");
        delay(1000);

        sht.setAddress(1);
        delay(500);  
        sht.setBaudrate(4800);
        delay(10);
        sht.begin(4800);
        
      }else{
        return;
      }
    }
  }

  if(sht.readAddress() == 1 && sht.readBaudrate() == 4800){
    Serial.println("Setup sensor to Factory Config: Address(0x01) & Baudrate(4800)");
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(sht.readAddress() == 1 && sht.readBaudrate() == 4800){

    dataSHTC3 data = sht.getData();

    Serial.print(data.temperatureC);
    Serial.print(F("°C\t"));
    Serial.print(data.temperatureF);
    Serial.print(F("°F\t"));
    Serial.print(data.humidity);
    Serial.println(F("%"));

    delay(1000);
  }
}
