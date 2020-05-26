
const int pin_LED = 13; // the pin number of LED
const int pin_btn = 34; // the pin number of button
int btn_state = 0; // the status vlaue of pin button

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //initialize serial at 115200 Baud
  
  pinMode(pin_LED, OUTPUT); // initialize pin LED as output pin
  pinMode(pin_btn, INPUT);  // initialize pin button as input pin

}

void loop() {
  // put your main code here, to run repeatedly:
  btn_state = digitalRead(pin_btn); // read state from pin button

  if(btn_state == HIGH){
    Serial.println("Button state is HIGH");
    digitalWrite(pin_LED, HIGH); // write HIGH to pin LED
  }else{
    Serial.println("Button state is LOW");
    digitalWrite(pin_LED, LOW); // write LOW to pin LED
  }

}
