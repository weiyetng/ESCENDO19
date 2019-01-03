#include <Servo.h> //include servo library

Servo myservo; //Declare myservo as a Servo object.

void setup() {
  myservo.attach(9); //Connect servo motor to pin 9
}

void loop() {
  myservo.write(100); //rotate 100 degree
  delay(1000); //wait for 1 second
  myservo.write(50); //rotate back to 50 degree
  delay(1000); //wait for 1 second
}
