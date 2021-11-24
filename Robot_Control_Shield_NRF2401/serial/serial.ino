/*
Remove any bluetooth module while uploading code to avoid
upload error
*/

void setup() 
{
Serial.begin(9600);

pinMode(2, INPUT); digitalWrite(2,HIGH);
pinMode(3, INPUT);digitalWrite(3,HIGH);
pinMode(4, INPUT);digitalWrite(4,HIGH);
pinMode(5, INPUT);digitalWrite(5,HIGH);
pinMode(6, INPUT);digitalWrite(6,HIGH);
pinMode(7, INPUT);digitalWrite(7,HIGH);

}

void loop() 
{
Serial.print("Joystick=  ");
Serial.print(analogRead(A2)); Serial.print("  ");
Serial.print(analogRead(A3)); Serial.print("  ");

Serial.print("Knob=  ");
Serial.print(analogRead(A5)); Serial.print("  ");

Serial.print("Switch=  ");
Serial.print(analogRead(A0)); Serial.print("  ");
Serial.print(analogRead(A1)); Serial.print("  ");

Serial.print("Buttons=  ");
Serial.print(digitalRead(3)); Serial.print("  ");
Serial.print(digitalRead(2)); Serial.print("  ");
Serial.print(digitalRead(4)); Serial.print("  ");
Serial.print(digitalRead(7)); Serial.print("  ");
Serial.print(digitalRead(5)); Serial.print("  ");
Serial.print(digitalRead(6)); Serial.print("  ");


Serial.println("  ");

}
