//***************************************************************************************************
//
//All codes were written and modified under the Research and Development Wing of Spectrum Engineering
//Consortium Limited, Dhaka.
//Author: Soumen Sikder Shuvo, Executive, R&D, SECL
//Last Modified: DD/MM/YYYY
//
//***************************************************************************************************

//The bluetooth module will send a string,
//if it is FORWARD the motor will anticlockwise run at a constant speed
//if it is BACK, the motor will run at constant speed clockwise
//if the string is STOP, the motor will stop

String flag;
const int stepPin = 11; // define pin for step
const int dirPin = 12; // define pin for direction

void setup() {
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
}

void loop() {
  
  if(Serial.available()) {
    flag=Serial.readString();
    Serial.println(flag);
    
    if(flag == "FORWARD") {
      digitalWrite(dirPin,HIGH);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500);
    }
    else if(flag == "BACK") {
      digitalWrite(dirPin,LOW);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500);
    }
    
    else if(flag == "STOP") {
      digitalWrite(dirPin,LOW);
      digitalWrite(stepPin,LOW);
    }
  }
}
