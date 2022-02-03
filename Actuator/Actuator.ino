int mspeed=0;
int RPWM = 5;
int LPWM = 6;
int cDelay; //cDelayMapped;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);

   pinMode(RPWM,OUTPUT);
   pinMode(LPWM,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  mspeed = 10;
  if( digitalRead(2) == LOW & digitalRead(3) == HIGH  ){
    mspeed = speedUp();
    analogWrite(RPWM,0);
    analogWrite(LPWM, mspeed);
    //delay(500);
    }
  else if( digitalRead(2) == HIGH & digitalRead(3) == LOW  ){
    mspeed = speedUp();
    analogWrite(RPWM,mspeed);
    analogWrite(LPWM, 0);
    //delay(500);
    }
  else{
    analogWrite(RPWM,0);
    analogWrite(LPWM, 0);
    }
}

int speedUp(){
  int cDelay = analogRead(A0);
  int newCustom = map(cDelay, 0, 1023, 50, 255);
  return newCustom;
}


// mpeed & Time Table
// 255- 19
// 51- 95
// 25- 210
// 
