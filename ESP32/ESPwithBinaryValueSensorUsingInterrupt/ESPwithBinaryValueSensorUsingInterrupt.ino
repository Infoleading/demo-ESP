/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#define timeSeconds 5

// Set GPIOs for pinLED and PIR Motion Sensor
const int pinLED = 13;
const int pinMotionSensor = 27;
const int pinSonicSensor = 4;
const int pinRainSensor = 5;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

// Checks if motion was detected, sets pinLED HIGH and starts a timer
void IRAM_ATTR detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  digitalWrite(pinLED, HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void IRAM_ATTR detectSonic(){
  Serial.println("Sonic Detected!!!");
  //for some case, the sensor will trigger the interrupt continus, you need to detach the interrupt in backcall function.
  detachInterrupt(digitalPinToInterrupt(pinSonicSensor));
  digitalWrite(pinLED,HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void IRAM_ATTR detectRain(){
  Serial.println("Rain Detected!!!");
  //for some case, the sensor will trigger the interrupt continus, you need to detach the interrupt in backcall function.
  digitalWrite(pinLED,HIGH);
  startTimer = true;
  lastTrigger = millis();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(pinMotionSensor, INPUT_PULLUP);
  pinMode(pinSonicSensor, INPUT);
  pinMode(pinRainSensor, INPUT);
  
  // Set pinMotionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(pinMotionSensor), detectsMovement, RISING);
  attachInterrupt(digitalPinToInterrupt(pinSonicSensor), detectSonic, RISING);
  attachInterrupt(digitalPinToInterrupt(pinRainSensor), detectRain, FALLING);

  // Set pinLED to LOW
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
}

void loop() {
  // Current time
  now = millis();
  // Turn off the pinLED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    //after the determination of execution, you need to attach interrupt again
    attachInterrupt(digitalPinToInterrupt(pinSonicSensor), detectSonic, HIGH);
    Serial.println("execution stopped...");
    digitalWrite(pinLED, LOW);
    startTimer = false;
  }
}
