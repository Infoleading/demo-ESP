#include <SoftwareSerial.h>

SoftwareSerial mySerial(9,8);
char val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  // read Message from Rx-0 Tx-1 and write to softwareSerial Rx-9 Tx-8
  if (Serial.available()>0){
    val = Serial.read();
    mySerial.print(val);
  }
  // read Message from Rx-9 Tx-8 and write to Serial Rx-0 Tx-1
  if (mySerial.available()>0){
    Serial.print(mySerial.readStringUntil('\n'));
  }
}
