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
int joyth= 5;
int joypos;
int knobpos;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); // set reading address
  radio.setPALevel(RF24_PA_MIN);// set min receiving power
    /*
   for long range 
   radio.setPALevel(RF24_PA_MAX);
   NRF will draw more current when set to high power
   */
  radio.startListening(); // set the tranceiver only as receiver
}

void loop() {
  if (radio.available()) 
  {
    radio.read(&data, sizeof(data));

    for (int i=0; i<sizeof(data); i++)
      {
        Serial.print(data[i]);
        Serial.print("  ");
      }
      Serial.println("  ");

    if (data[0] < 128+joyth && data[0] > 128-joyth)
    {
      Serial.print("Joystick  at Center(L-R)");
    }
    if (data[0] <= 128-joyth)
    {
      joypos = map(data[0], 128-joyth, 0, 0, 100);
      Serial.print("Joystick at ");
      Serial.print(joypos);
      Serial.print("% left");
    }
    if (data[0] >= 128+joyth)
    {
      joypos = map(data[0], 128+joyth, 255, 0, 100);
      Serial.print("Joystick at ");
      Serial.print(joypos);
      Serial.print("% right");
    }

    Serial.print(" ");
    
    if (data[1] < 128+joyth && data[1] > 128-joyth)
    {
      Serial.print("Joystick at Center(U-D)");
    }
    if (data[1] <= 128-joyth)
    {
      joypos = map(data[1], 128-joyth, 0, 0, 100);
      Serial.print("Joystick at ");
      Serial.print(joypos);
      Serial.print("% down");
    }
    if (data[1] >= 128+joyth)
    {
      joypos = map(data[1], 128+joyth, 255, 0, 100);
      Serial.print("Joystick at ");
      Serial.print(joypos);
      Serial.print("% up");
    }

    Serial.print(" ");

    Serial.print("Knob at ");
    Serial.print(map(data[2], 0, 255, 0, 100));
    Serial.print(" percent position");

    Serial.print(" ");
    if (data[3]) {Serial.print("B1 rested");}
    else {Serial.print("B1 pushed");}

    Serial.print(" ");
    if (data[4]) {Serial.print("B2 rested");}
    else {Serial.print("B2 pushed");}

    Serial.print(" ");
    if (data[5]) {Serial.print("A (Red) rested");}
    else {Serial.print("A (Red) pushed");}

    Serial.print(" ");
    if (data[6]) {Serial.print("B (Green) rested");}
    else {Serial.print("B (Green) pushed");}

    Serial.print(" ");
    if (data[7]) {Serial.print("X (Yellow) rested");}
    else {Serial.print("X (Yellow) pushed");}

    Serial.print(" ");
    if (data[8]) {Serial.print("Y (White) rested");}
    else {Serial.print("Y (White) pushed");}

    Serial.print(" ");
    if (data[10]) {Serial.print("S1 ON");}
    else {Serial.print("S1 OFF");}

    Serial.print(" ");
    if (data[9]) {Serial.print("S2 ON");}
    else {Serial.print("S2 OFF");}
  }
}
