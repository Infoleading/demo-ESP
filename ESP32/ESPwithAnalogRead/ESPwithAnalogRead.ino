// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
const int apinRain = 14;
const int dpinRain = 5;

// variable for storing the potentiometer value
int analogValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Reading potentiometer value
  analogValue = analogRead(apinRain);
  Serial.println(analogValue);
  delay(50);
}
