//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

bool trang_thai;
//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();

  trang_thai = 0;

  pinMode(13, OUTPUT);
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    
    trang_thai = ~trang_thai;
    digitalWrite(13, trang_thai);

    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
