void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float volt = analogRead(A0) * 5.0 / 1024.0;
  float amps = volt/10000;
  float microamps = amps * 1000000;
  float lux = microamps * 2.0;

  Serial.print("Light Intensity: ");
  Serial.print(lux, 2);
  Serial.print(" (lux)");
  Serial.println();
  delay(100);
}
