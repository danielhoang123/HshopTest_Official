#include <SoftwareSerial.h>

SoftwareSerial jdy33(2, 3); //RX, TX

void setup() {
  // put your setup code here, to ru`n once:
  Serial.begin(9600);
  jdy33.begin(9600);
  jdy33.println("AT");
}

void loop() {

  //  nhapcode();
  CheckPC_Serial();
  CheckBL_Serial();
  //JDY33 to Arduino

  //  if(jdy33.available()) {
  //    Serial.write(jdy33.read());
  //  }
  //
  //  //Arduino to JDY33
  //  if(Serial.available()) {
  //      jdy33.write(Serial.read());
  //  }

}

int nhapcode() {
  if (Serial.available()) {

    char value = Serial.read();

    if (value == '1') {
      Serial.println("Day la so 1");
      delay(5);
    }
    else if (value == '2') {
      Serial.println("Day la so 2");
      delay(5);
    }
  }
}

void CheckBL_Serial1() {
  if (jdy33.available()) {
    String data = jdy33.readStringUntil('\n');
    //    int numberData = data.toInt();
    Serial.println(data);

  }
}

bool CheckBL_Serial() {
  if (jdy33.available()) {
    String data = jdy33.readStringUntil('\n');
    //    int numberData = data.toInt();
    Serial.println(data);
    Serial.println(data.indexOf("+OK"));
    if (data.indexOf("+OK") > -1) {
      return true;
    }
  }
  return false;
}

bool CheckPC_Serial() {
  if (Serial.available()) {
    String data1 = Serial.readStringUntil('\n');
    int numberData1 = data1.toInt();
    Serial.println(numberData1 + 1);
    //    jdy33.println("AT");
    if (SendAT("AT")) {
      Serial.println("AT OK");
    } else {
      Serial.println("AT FAIL");
    }

  }
}

void setupBLE(unsigned int num) {
  if (SendAT("AT")) {
    Serial.println("AT OK");
  } else {
    Serial.println("AT FAIL");
  }

  if (SendAT("AT+NAMEMKE_M15_" + String(num)) ) {
    Serial.println("AT +OK");
  } else {
    Serial.println("AT FAIL");
  }
}

bool SendAT(String str_cm) {
  while (jdy33.available()) jdy33.read();

  jdy33.println("AT");
  delay(10);

  return CheckBL_Serial();
}
