#define LED 3 //Set pin 3 to be LED
#define varRes A3 //Set pin A3 to be variable resistor
int brightness; //Declare brightness as an integer
void setup() {
  pinMode(LED, OUTPUT); //Tell pin 3 to output voltage
  pinMode(varRes, INPUT); //Tell pin A3 to read the voltage
  Serial.begin(9600); //Initialise serial monitor and set communication via 9600
}

void loop() {
  brightness = analogRead(varRes); //Pin A3 is used to read the voltage. Analog read is used so a range of values can be obtained.
  analogWrite(LED,brightness); //Pin 3 is used to output the voltage. Pin 3 is used as it is a PWM pin. ONLY PWM pin can analogWrite. Analog pin cannot output analog values.
  Serial.println(brightness); //This is different from C. There is no need to put a specifier for print!
}
