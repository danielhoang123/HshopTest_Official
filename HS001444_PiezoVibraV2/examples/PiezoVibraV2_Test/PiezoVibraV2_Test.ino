#define Dig_pin 7

int Dig_out = LOW;
int Ana_out = 0;
 
void setup() {
   Serial.begin(115200);
   Serial.print("Analog");Serial.print(",");
   
   Serial.print("Digital");Serial.print(",");
   Serial.print("Min");Serial.print(",");
   
   Serial.println("Max");
}
 
void loop() {
   Dig_out = digitalRead(Dig_pin)*10;
   Ana_out = analogRead(A0);
   
   Serial.print(Ana_out);Serial.print(",");
   Serial.print(Dig_out);Serial.print(",");
   Serial.print(0);Serial.print(",");
   Serial.println(200);
}
   
