/*
 * this project contain two sub-steps
 * at the first step, we only use ledPin=13 to test the PWM
 * at the second step, we add another two ledPins to test the PWM, you'll find that besed on the channel concepts, you can controll any pins by the same pwm channel.
 */

// the number of the LED pin
const int ledPin = 13;  // 16 corresponds to GPIO16
const int ledPin2 = 27;
const int ledPin3 = 33;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;  // 0-15
const int resolution = 8;  // 1-16
 
void setup(){
  
  ledcSetup(ledChannel, freq, resolution); // configure LED PWM functionalitites 
  
  ledcAttachPin(ledPin, ledChannel); // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin2, ledChannel); 
  ledcAttachPin(ledPin3, ledChannel);
}
 
void loop(){
  
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    //for 8 bit resolution, you can use 0-255 steps to describe the dutyCycle
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15); //15ms
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(15);
  }
}
