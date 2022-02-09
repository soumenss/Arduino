/*  This code is to stress test an Actuator. 
 *  The only two inputs here are mspeed which will determine the speed
 *  of the Actuator, and differ which will select after how many seconds
 *  the process will be repeated.
 *  the speed will be highest at mpeed = 255 and below than 25 the Actuator starts jerking.
 */

byte mspeed = 250;
int RPWM = 5;
int LPWM = 6;
int differ = 15;

void setup() {
  Serial.begin(9600);
  pinMode(RPWM,OUTPUT);
  pinMode(LPWM,OUTPUT);
}

void loop() {
  int ttime = millis()/(1000*differ);
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
