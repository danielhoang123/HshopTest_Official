#include <SoftwareSerial.h>

SoftwareSerial jdy33(2, 3); //RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  jdy33.begin(9600);
}

void loop() {

  CheckPC_Serial();
  CheckBL_Serial();
//  testATManual();
  
}

bool CheckBL_Serial() {
  if (jdy33.available()) {
    String data = jdy33.readStringUntil("\n");
    Serial.println(data);
    //Serial.println(data.indexOf("OK"));
    if (data.indexOf("OK") > -1) {
      return true;
    }
  }
  return false;
}

bool CheckPC_Serial() {

  if (Serial.available()) {
    String data1 = Serial.readStringUntil("\n");
    SendAT(data1);
    delay(90);
    SendATName(data1);
    delay(90);
    SendATNamb(data1);
    delay(90);
    SendATBaud(data1);
    delay(90);
  }
}

bool SendAT(String num1) {
  
  while (jdy33.available()) jdy33.read();
  
  jdy33.println("AT");
  delay(40);

  return CheckBL_Serial();
}

bool SendATName(String num2) {
  
  while (jdy33.available()) jdy33.read();
  
  jdy33.println("AT+NAMEMKE_M15_" + String(num2));
  delay(30);
  
  return CheckBL_Serial();
}

bool SendATNamb(String num3) {
  
  while (jdy33.available()) jdy33.read();
  
  jdy33.println("AT+NAMBMKE_M15B_" + String(num3));
  delay(30);
  
  return CheckBL_Serial();
}

bool SendATBaud(String num4) {
  
  while (jdy33.available()) jdy33.read();\
  
  jdy33.println("AT+BAUD4");
  delay(30);

  jdy33.println("AT+NAME");
  delay(30);

  jdy33.println("AT+NAMB");
  delay(30);
  
  jdy33.println("AT+BAUD");
  delay(30);
  return CheckBL_Serial();
}

void testATManual() {

    //jdy to arduino
    if(jdy33.available()) {
      Serial.write(jdy33.read());
    }
    
    //Arduino to JDY33
    if(Serial.available()) {
        jdy33.write(Serial.read());
    }
}
