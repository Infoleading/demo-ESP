#include <Adafruit_NeoPixel.h>
int PIN = 6;
int NUMPIXELS = 16;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
//  if(analogRead(A5)>200){
//    digitalWrite(11,HIGH);
//    delay(5000);
//    digitalWrite(11,LOW);
  int numPixel = 16*analogRead(A5)/500;
  Serial.println(numPixel);
  for(int i=0; i<16; i++){
      pixels.setPixelColor(i, pixels.Color(0,0,0));
  } 
  pixels.show();
  for(int i=0; i<numPixel; i++){
      pixels.setPixelColor(i, pixels.Color(0,150,0));
      delay(10);
      pixels.show();
  }
}
