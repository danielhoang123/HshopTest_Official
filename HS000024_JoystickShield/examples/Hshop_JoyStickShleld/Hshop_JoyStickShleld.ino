int up_button = 2;
int down_button = 4;
int left_button = 5;
int right_button = 3;
int start_button = 6;
int select_button = 7;
int analog_button = 8;
int x_axis = A0;
int y_axis = A1;
int buttons[] = {up_button, down_button, left_button, right_button, start_button, select_button, analog_button};


void setup() {
  for (int i; i < 7; i++)
  {
   pinMode(buttons[i], INPUT);
   digitalWrite(buttons[i], HIGH);
  }
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(up_button) == 0){
    delay(25);
    if(digitalRead(up_button) == 0){
      Serial.println("UP");
      delay(200);
    }  
  }
  else if(digitalRead(down_button) == 0){
    delay(25);
    if(digitalRead(down_button) == 0){
      Serial.println("DOWN");
      delay(200);
    }  
  }
  else if(digitalRead(left_button) == 0){
    delay(25);
    if(digitalRead(left_button) == 0){
      Serial.println("LEFT");
      delay(200);
    }  
  }
  else if(digitalRead(right_button) == 0){
    delay(25);
    if(digitalRead(right_button) == 0){
      Serial.println("RIGHT");
      delay(200);
    }  
  }
  else if(digitalRead(start_button) == 0){
    delay(25);
    if(digitalRead(start_button) == 0){
      Serial.println("START");
      delay(200);
    }  
  }
  else if(digitalRead(select_button) == 0){
    delay(25);
    if(digitalRead(select_button) == 0){
      Serial.println("SELECT");
      delay(200);
    }  
  }
  else if(digitalRead(analog_button) == 0){
    delay(25);
    if(digitalRead(analog_button) == 0){
      Serial.println("ANALOG");
      delay(200);
    }  
  } 
  else if((map(analogRead(x_axis), 0, 1023, 0, 255)) != 125){
    Serial.println(map(analogRead(x_axis), 0, 1023, 0, 255));
    delay(200);
  }
  else if((map(analogRead(y_axis), 0, 1023, 0, 255)) != 126){
    Serial.println(map(analogRead(y_axis), 0, 1023, 0, 255));
    delay(200);
  }  
}
 
