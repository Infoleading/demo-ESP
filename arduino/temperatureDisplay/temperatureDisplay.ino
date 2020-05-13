#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPIN 3
#define DHTTYPE 11

LiquidCrystal_I2C lcd(0x27,20,4);
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(9,8);
char val;

void setup() {
  // put your setup code here, to run once:
  val='';
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (Serial.available()>0){
    item = Serial.read();
    mySerial.print(val);
  }
  if (mySerial.available()>0){
    Serial.print(mySerial.readStringUntil('\n'));
  }
}
