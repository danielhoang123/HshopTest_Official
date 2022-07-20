 // (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#define SIGNAL_PIN 2

void setup()
{
  Serial.begin(9600);
  pinMode(SIGNAL_PIN, INPUT);
  Serial.println("Hshop.vn Testing: ");
}

void loop() {
  if(digitalRead(SIGNAL_PIN)==HIGH) {
    Serial.println("Phat hien than nhiet");
  } else {
    Serial.println("Khong phat hien than nhiet");
  }
  delay(1000);
}
