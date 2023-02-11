const int sensorPin = A0;

//kalman variables
float varVolt = 1.12184278324081E-05;
float varProcess = 1e-8;
float Pc = 0.0;
float G = 0.0;
float P = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xe = 0.0;

int WINDOW_SIZE = 50;
int INDEX = 0;
float VALUE = 0;
float SUM = 0;
float READING[50];
float AVERAGE = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(sensorPin);
  float voltage = sensorVal * 0.488;

  //kalman process
  Pc = P + varProcess;  //predict covariance
  Xp = Xe;              //predict state

  G = Pc/(Pc+varVolt);

  Zp = Xp;
  Xe =  G*(voltage-Zp)+Xp;
  P=(1-G)*Pc; 

  Serial.print(voltage);
  Serial.print(",");
  Serial.print(Xe);

  SUM = SUM - READING[INDEX];

  READING[INDEX] = voltage;
  SUM = SUM + voltage;
  INDEX = (INDEX+1) % WINDOW_SIZE;

  AVERAGE = SUM / WINDOW_SIZE;

  Serial.print(",");
  Serial.println(AVERAGE);
  delay(20); 
  
}
