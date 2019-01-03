#define LED 13 //Set LED as pin 13
unsigned long time; //declare time as a variable. Unsigned = positive values only, Long = to increase the range of values which time can take
void setup() {
  pinMode(LED, OUTPUT); //tell pin 13 to output a voltage
}

void loop() {
  time = millis();
  if(time%50 == 0){ //Modulo operator, this condition is only true when time is a multiple of 50. So when time is a multiple of 50, the pin output 5V, turning it on. Or else, the LED is turned off
    digitalWrite(LED, HIGH); //tell pin 13 to output a high voltage, 5V
  }
  else{
    digitalWrite(LED,LOW); //tell pin 13 to output a low voltage, grd
  }
}
