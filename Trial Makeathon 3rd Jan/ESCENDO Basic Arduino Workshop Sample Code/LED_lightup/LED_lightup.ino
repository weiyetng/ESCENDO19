#define LED 3 //Set LED to be pin 3
void setup() {
  pinMode(LED, OUTPUT); //Pin 3 will be used to output a voltage
}

void loop() {
  digitalWrite(LED, HIGH); //Pin 3 will output a high voltage, 5V
}
