#define joyX A0
#define joyY A1
#define swit A2
//#define ledpin 13
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int sValue = digitalRead(swit);
 
  //print the values with to plot or view
  Serial.print(sValue);
  Serial.print("\t");
  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);
//  digitalWrite(ledpin, sValue);
}
