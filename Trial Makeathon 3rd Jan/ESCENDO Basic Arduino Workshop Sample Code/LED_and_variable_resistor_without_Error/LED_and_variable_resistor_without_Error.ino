#define LED 3 //Set pin 3 to be LED
#define varRes A3 //Set pin A3 to be variable resistor
int brightness, mappedbrightness; //Declare brightness and roundedbrightness as an integer
void setup() {
  pinMode(LED, OUTPUT); //Tell pin 3 to output voltage
  pinMode(varRes, INPUT); //Tell pin A3 to read the voltage
}

void loop() {
  brightness = analogRead(varRes); //Pin A3 is used to read the voltage. Analog read is used so a range of values can be obtained.
  mappedbrightness = map(brightness,0,1023,0,255); //ensure that values obtained from analogRead is restricted to (0,255) instead of (0,1023)
  analogWrite(LED,mappedbrightness); //Pin 3 is used to output the voltage. Pin 3 is used as it is a PWM pin. ONLY PWM pin can analogWrite. Analog pin cannot output analog values.
}
