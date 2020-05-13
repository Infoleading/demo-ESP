/*
 * 智能家居原型设计
 * 1. 开关门控制   0-关门  1-开门
 * 2. 开关灯控制   2-关灯  3-开灯
 * 3. 室内温度显示 4-发送温度数据  5-接收温度数据
 * 
 * 
 * 
 */
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

#define PINLIGHT 4
#define PINSERVO 10
#define PINSOFTRX 9
#define PINSOFTTX 8
#define PINDHT 3
#define DHTTYPE 11
#define PINFAN1 11
#define PINFAN2 12
#define PINSONIC A0
#define PINBELT 5

//全局变量
int signal = -1; //串口信号量
int pos = 0; //门角度 0-90
int threshold;
int NUMPIXELS = 16;
float temperature=0;
float oldTemperature;
float humidity=0;
float oldHumidity;
int numPixel;

// 全局对象
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINBELT, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial(PINSOFTRX,PINSOFTTX);
Servo myservo; // 车库舵机
Servo srvDoor; //门控舵机
Servo srvWindow; //窗控舵机
DHT dht(PINDHT, DHTTYPE);  // 温度控制
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //串口波特率初始化
  dht.begin(); //
  mySerial.begin(9600);
  pixels.begin();
  
  myservo.attach(PINSERVO);
  myservo.write(0); // 初始化关门
  pinMode(PINSONIC,INPUT);
  pinMode(PINLIGHT,OUTPUT);
  pinMode(PINFAN1,OUTPUT);
  pinMode(PINFAN2,OUTPUT);
  pinMode(PINDHT,INPUT);
  lcd.init();
  lcd.backlight();
  threshold = 30;
}

void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.print("humidity=");
  Serial.println(humidity); // 查看温度数据
  Serial.print("temperature=");
  Serial.println(temperature); // 查看温度数据
  
  if(mySerial.available()){
    
    signal = mySerial.parseInt(); // 获取信号量
    Serial.print("singal=");
    Serial.println(signal); // 向0/1串口输出调试信息
    
    switch(signal){
      case 1: // 关门
        ctrlDoor(0);
        break;
      case 0: // 开门
        ctrlDoor(90);
        break;
      case 3: // 关灯
        ctrlLight(0);
        break;
      case 2: // 开灯
        ctrlLight(1);
        break;
      case 4: // 发送温度
        mySerial.print(temperature);
        break;
      case 5: // 读取温度
        while(1){
          if(mySerial.available()){
            threshold = mySerial.parseInt();
            Serial.print("threshold=");
            Serial.println(threshold);
            break;
          }
        } 
    }
  }

  // 风扇自动控制
  if(temperature>=threshold){
    digitalWrite(PINFAN1, LOW);
    digitalWrite(PINFAN2, HIGH);
  }
  else{
    digitalWrite(PINFAN1, LOW);
    digitalWrite(PINFAN2, LOW);
  }
   
  lcd.setCursor(3,0);
  lcd.print(temperature);
  lcd.print(" c");

  lcd.setCursor(7,1);
  lcd.print(humidity);
  lcd.print(" %");

  numPixel = 16*analogRead(PINSONIC)/50;
  Serial.print("PINSONIC=");
  Serial.println(analogRead(PINSONIC));
  for(int i=0; i<16; i++){
      pixels.setPixelColor(i, pixels.Color(0,0,0));
  } 
  pixels.show();
  for(int i=0; i<numPixel; i++){
      pixels.setPixelColor(i, pixels.Color(0,150,0));
      delay(20);
      pixels.show();
  }

  delay(200);
}

/*
 * 门控
 * angle 门的角度 0-90
 * servo 舵机对像
 */
void ctrlDoor(int angle, Servo servo){
  pos = angle;
  for (; pos <= angle; pos += 1) {
    servo.write(pos);              
    delay(15);
  }
  for (; pos >= angle; pos -= 1) {
    servo.write(pos);              
    delay(15);
  }
}

/*
 * 灯控
 * onoff 0-关灯  1-开灯
 */
void ctrlLight(int onoff){
  if(onoff==0)
    digitalWrite(PINLIGHT, LOW);
  else
    digitalWrite(PINLIGHT, HIGH);
}
