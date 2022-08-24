/*
 * Original sourse: https://playground.arduino.cc/Code/Keypad
 * This is the Arduino code for 4x4 black keypad
 * watch the video for details and demo https://youtu.be/1rfrvOTxtrg  
 *  * 
 * Written by Ahmad S. for Robojax Video channel www.Robojax.com
 * Date: April 15, 2018, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * this code has been downloaded from http://robojax.com/learn/arduino/
 * 
 */
/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //4 hang
const byte COLS = 4; //4 cot
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// ket noi cac pin cua keypad phai --> trai <=> 2 --> 9
byte rowPins[ROWS] = {5,4,3,2}; //chan hang cua keypad
byte colPins[COLS] = {9,8,7,6}; //chan cot cua keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
    
  if (key){
  Serial.print("Phim ");
  Serial.println(key);
  }
}
