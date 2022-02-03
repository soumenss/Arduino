byte mspeed = 250;
int RPWM = 5;
int LPWM = 6;

void setup() {
  Serial.begin(9600);
  pinMode(RPWM,OUTPUT);
  pinMode(LPWM,OUTPUT);
}

void loop() {
  int ttime = millis()/15000;
  if(ttime%2) {
    analogWrite(RPWM,0);
    analogWrite(LPWM, mspeed);
  }
  else {
    analogWrite(LPWM,0);
    analogWrite(RPWM, mspeed);
  }
//  Serial.print(RPWM, LPWM);
}
