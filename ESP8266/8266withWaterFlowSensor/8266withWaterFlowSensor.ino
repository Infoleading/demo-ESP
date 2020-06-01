/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Set GPIOs for LED and PIR Motion Sensor
const int pinWaterFlowSensor = 13;
unsigned long puls;

// Checks if motion was detected, sets LED HIGH and starts a timer
ICACHE_RAM_ATTR void detectsFlow() {
  puls++;
  Serial.println(puls);
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(pinWaterFlowSensor, INPUT);
  
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(pinWaterFlowSensor), detectsFlow, RISING);

  // initalize plus
  puls=0;
}

void loop() {

}
