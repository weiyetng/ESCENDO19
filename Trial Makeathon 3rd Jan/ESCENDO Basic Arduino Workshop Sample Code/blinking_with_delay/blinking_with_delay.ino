#define LED 13 //Set LED to be pin 13
void setup() {
  pinMode(LED, OUTPUT); //Tell pin 13 to output voltage
}

void loop() {
  digitalWrite(LED, HIGH); //Tell pin 13 to output high voltage, 5V
  delay(1000); //delay 1 second
  digitalWrite(LED,LOW); //Tell pin 13 to output low voltage, ground
  delay(1000); //delay 1 second
}
