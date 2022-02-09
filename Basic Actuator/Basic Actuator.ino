/* This is a sample code to run an actuator at a variable speed using an Arduino and Pot.
 *  Pin 5 and Pin 6 will give the PWM pulses to the motor controller.
 *  Pin 5 as RPWM and Pin 6 as LPWM. So these two pins will be connected to that of the Motor controllers.
 *  Pin 2 and Pin 3 will be decision of weather the Actuator will be extended or contracted. 
 *  If Pin 2 is LOW and Pin 3 is High, RPWM will be on and LPWM will be 0. Reverse will happen with Pin 2 is High
 *  and Pin 3 is Low.
 *  A 5V will be scaled through a POT and given input in A0 where the signal will be read and mapped
 *  to determine the intended speed to the Motor controller. The Motor will run at highest speed 
 *  when PWM is 255. More will not make any difference. Below 25 the motor starts jerking and doesn't work.
 *  SpeedUp function does the mapping of the PWM pulse
 */

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
