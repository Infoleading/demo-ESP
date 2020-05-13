#include <SoftwareSerial.h>

SoftwareSerial mySerial(9,8);
int switch1=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(4,OUTPUT);
}

void loop() {

  // put your main code here, to run repeatedly:
  if(mySerial.available()>0){
    switch1 = mySerial.parseInt();
    Serial.print(switch1);
  }
  if(switch1==1)
    digitalWrite(4, HIGH);
  if(switch1==0)
    digitalWrite(4, LOW);
}
