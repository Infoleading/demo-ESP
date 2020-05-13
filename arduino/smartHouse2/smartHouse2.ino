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

#define PIN_SERVO_DOOR 10
#define PIN_SERVO_WINDOW 9 
#define PIN_SERVO_GARGAGE 11
#define PIN_DHT 3
#define DHT_TYPE 11
#define PIN_SONIC A0
#define PIN_LIGHT 4
#define PIN_TRIG A0
#define PIN_ECHO A1

//全局变量
int signal = -1; //串口信号量
int pos = 0; //门角度 0-90
int dist = 0;
float temperature=0;
float oldTemperature;
float humidity=0;
float oldHumidity;

// 全局对象
Servo srvGargage; // 车库舵机
Servo srvDoor; //门控舵机
Servo srvWindow; //窗控舵机
DHT dht(PIN_DHT, DHT_TYPE);  // 温度控制
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //串口波特率初始化

  // 端口模式 
  pinMode(PIN_SONIC,INPUT);
  pinMode(PIN_LIGHT,OUTPUT);
  pinMode(PIN_DHT,INPUT);
  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECHO,INPUT);
  
  dht.begin(); // 初始化dht11
  
  srvDoor.attach(PIN_SERVO_DOOR);
  srvDoor.write(0); // 初始化关门
  srvWindow.attach(PIN_SERVO_WINDOW);
  srvWindow.write(0); // 初始化关门  
  srvGargage.attach(PIN_SERVO_GARGAGE);
  srvGargage.write(0); // 初始化关门    

  lcd.init(); //初始化lcd
  lcd.backlight();
}

void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.print("humidity=");
  Serial.println(humidity); // 查看温度数据
  Serial.print("temperature=");
  Serial.println(temperature); // 查看温度数据

  dist = sonicDist();
  Serial.print("Distance:");
  Serial.print(dist);
  Serial.println("cm");  

  //---------------------
  lcd.setCursor(3,0);
  lcd.print(temperature);
  lcd.print(" c");

  lcd.setCursor(7,1);
  lcd.print(humidity);
  lcd.print(" %");

  // --------------------
  if(temperature>25){
    ctrlLight(1, PIN_LIGHT);
    ctrlDoor(0, srvWindow);
  }
  else{
    ctrlLight(0, PIN_LIGHT);
    ctrlDoor(90, srvWindow);
  }

  if(dist<10){
    ctrlLight(1, PIN_LIGHT);
    ctrlDoor(0, srvDoor);
  }
  else{
    ctrlLight(0, PIN_LIGHT);
    ctrlDoor(90, srvDoor);
  }

  delay(200);
}

/*
 * 缓慢门控
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
 * pinLi
 */
void ctrlLight(int onOff, int pinLight){
  if(onOff==0)
    digitalWrite(pinLight, LOW);
  else
    digitalWrite(pinLight, HIGH);
}

/*
 * 
 * 
 * 
 *
 */
int sonicDist(){
  int dist = 0;
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(8);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10); // 维持10毫秒高电平用来产生一个脉冲
  digitalWrite(PIN_TRIG, LOW);
  dist = pulseIn(PIN_ECHO, HIGH) / 58.00;  // 读取脉冲的宽度并换算成距离
  return dist;
}
