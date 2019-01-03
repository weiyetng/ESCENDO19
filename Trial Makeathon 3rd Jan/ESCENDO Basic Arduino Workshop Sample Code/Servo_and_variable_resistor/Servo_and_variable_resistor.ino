/*Make the variable into a “joy stick”, such that when the variable resistor is turned to the left beyond a certain point, 
the servo turns left. When the variable resistor is turned to the right beyond a certain point, the variable resistor turns right. */


#include <Servo.h> //include servo library

Servo myservo; //Declare a Servo object, named myservo
static int pos; //Declare position as an integer

void setup() {
  myservo.attach(9);// Attach pin 9 to servo motor
}

void loop() {
   int i = analogRead(A2); // Read the voltage using A2
   if(i<200&&pos<180){ //If the voltage falls below 200 (approximately 1V) when it is turned to the left, and the position is less than 180 degress, turn the servo to the left.
    pos++; //increment position by 1
    myservo.write(pos); //turn the servo to the new position
    delay(5); //pause for 5 milliseconds
   }
   if(i>800&&pos>0){ //If the voltage lies above 800 (approximately 4V) when it is turned to the right, and the position is more than 0 degres, turn the servo to the right.
    pos--; //decrement position by 1
    myservo.write(pos); //turn the servo to the new position
    delay(5); //pause for 5 milliseconds
   }
}
