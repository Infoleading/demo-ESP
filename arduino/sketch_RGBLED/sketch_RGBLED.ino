void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
  delay(1);
  digitalWrite(2,LOW);
  delay(1);
}
