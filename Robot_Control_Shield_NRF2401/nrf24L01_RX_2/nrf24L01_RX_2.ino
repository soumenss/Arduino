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
        // Serial.print(data[i]);
        // Serial.print("  ");
      }
      Serial.println("  ");

    if (data[0] < 128+joyth && data[0] > 128-joyth)
    {
      Serial.print("JS: Center(L-R)");
    }
    if (data[0] <= 128-joyth)
    {
      joypos = map(data[0], 128-joyth, 0, 0, 100);
      Serial.print("JS: ");
      Serial.print(joypos);
      Serial.print("% Left");
    }
    if (data[0] >= 128+joyth)
    {
      joypos = map(data[0], 128+joyth, 255, 0, 100);
      Serial.print("JS: ");
      Serial.print(joypos);
      Serial.print("% Right");
    }

    Serial.print(" ");
    
    if (data[1] < 128+joyth && data[1] > 128-joyth)
    {
      Serial.print("JS: Center(U-D)");
    }
    if (data[1] <= 128-joyth)
    {
      joypos = map(data[1], 128-joyth, 0, 0, 100);
      Serial.print("JS: ");
      Serial.print(joypos);
      Serial.print("% Down");
    }
    if (data[1] >= 128+joyth)
    {
      joypos = map(data[1], 128+joyth, 255, 0, 100);
      Serial.print("JS: ");
      Serial.print(joypos);
      Serial.print("% Up");
    }

    Serial.print(" ");

    Serial.print("Knob: ");
    Serial.print(map(data[2], 0, 255, 0, 100));
    Serial.print("%");

    String ons = "ON:";
    String offs = "OFF:";

    if (!data[3]) {ons+= " B1";}
    else {offs+=" B1";}

    if (!data[4]) {ons+= " B2";;}
    else {offs+= " B2";}

    if (!data[5]) {ons+= " A";}
    else {offs+= " A";}

    if (!data[6]) {ons+= " B";}
    else {offs+= " B";}

    if (!data[7]) {ons+= " X";}
    else {offs+= " X";}

    if (!data[8]) {ons+= " Y";}
    else {offs+= " Y";}

    if (data[10]) {ons+= " S1";}
    else {offs+= " S1";}

    if (data[9]) {ons+= " S2";}
    else {offs+= " S2";}

    if ( ons.length() > 4)
    {
      Serial.print(" ");
      Serial.print(ons);
    }
    
    if ( offs.length() > 5)
    {
      Serial.print(" ");
      Serial.print(offs);
    }
    
  }
}
