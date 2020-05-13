#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(9,8);
Servo myservo;

int switch1 = 2;
int pos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(10);
  myservo.write(0);
  pinMode(4,OUTPUT);
}

void loop() {
  switch1=2;
  // put your main code here, to run repeatedly:
  if(mySerial.available()>0){
    switch1 = mySerial.parseInt();
    Serial.print(switch1);
  }
  if(switch1==1){
    digitalWrite(4, HIGH);
    for (; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              
      delay(15);
    }
  }
  if(switch1==0){
    digitalWrite(4, LOW);
    for (; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              
      delay(15);
    }
  }
}
