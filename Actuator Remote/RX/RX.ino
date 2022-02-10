 /*
This code uses "RF24" library. It's provided in the "NRF24" folder as zip file.
To install this library, open Arduino IDE, then Sketch >> Include Library >> Add .Zip Library
and then browse to the Radiohead.zip file.

Pin connections

MOSI --->> 11
MISO --->> 12
SCK --->> 13
VCC --->> 3.3V
GND --->> GND
CE --->> 8
CSN --->> 10

you can change CE & CSN if needed. Change code accordingly
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 10); // CE, CSN; you can change these 2 pins if needed

const byte address[6] = {192,168,0,255,17,48}; 
/*
change it for security. Should be same for TX & RX
all 6 bytes should be between 0-255
 */
byte data[11]; // this is where controller data is saved.
int piezoPin = 3;
byte mspeed=0;
int RPWM = 5;
int LPWM = 6;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); // set reading address
  radio.setPALevel(RF24_PA_MAX);// set min receiving power
    /*
   for long range 
   radio.setPALevel(RF24_PA_MAX);
   NRF will draw more current when set to high power
   */
  radio.startListening(); // set the tranceiver only as receiver
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    for (int i=2; i<5; i++)
      {
         Serial.print(data[i]);
         Serial.print("  ");
      }
      Serial.println("  ");

    if(data[3]==1 & data[4]==0) {
      mspeed = speedUp();
      analogWrite(RPWM,0);
      analogWrite(LPWM, mspeed);
    }
    else if(data[3]==0 & data[4]==1) {
      mspeed = speedUp();
      analogWrite(RPWM,mspeed);
      analogWrite(LPWM, 0);
    }
    else{
      analogWrite(RPWM,0);
      analogWrite(LPWM, 0);
    }
  }
  else
  {
    tone(piezoPin, 4000, 500); 
    Serial.println("No RF Signal");
    delay(1000);
  }
}

int speedUp(){
  int newCustom = map(data[2], 0, 256, 50, 250);
  return newCustom;
}
