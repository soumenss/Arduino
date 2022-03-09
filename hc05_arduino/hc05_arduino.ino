// **********************************************************************************************************************

// All codes were written and modified under the Research and Development Wing of Spectrum Engineering
// Consortium Limited, Dhaka.
// Author: Soumen Sikder Shuvo, Executive, R&D, SECL
// Last Modified: DD/MM/YYYY

// ***********************************************************************************************************************

/*
 * Possible string values:
 * a (to turn the LED on)
 * b (tor turn the LED off)
*/

char junk;
String inputString="";

void setup()
{
  Serial.begin(9600); // set the baud rate to 9600, same should be of your Serial Monitor
  pinMode(13, OUTPUT);
}

void loop()
{
  if(Serial.available())
  {
    while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar; //make a string of the characters coming on serial
    }
    
    Serial.println(inputString);
    
    while (Serial.available() > 0)
    {
      junk = Serial.read(); // clear the serial buffer
    }
    
    if(inputString == "f") //in case of 'a' turn the LED on
    {
      digitalWrite(13, HIGH);
    }
    else if(inputString == "b") //in case of 'b' turn the LED off
    {
      digitalWrite(13, LOW);
    }
    
    inputString = "";
  }
}
