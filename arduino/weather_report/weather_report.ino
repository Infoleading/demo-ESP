#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal_I2C.h>

EthernetClient client;
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char server[] = "restapi.amap.com";
unsigned long microsBegin, microsEnd, period=1800;
boolean updated;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  lcd.init();
  lcd.backlight();
  
  if(Ethernet.begin(mac)==1){ // =1 获取IP成功  =0 获取IP失败
    Serial.print("Successfully assigned IP address from DHCP: ");
    Serial.println(Ethernet.localIP());
  }else{
    Serial.println("Failed to assign IP address!");
  }
  
  microsBegin = micros()-(period-1)*1000000; // 第一次取29分59秒前的一个时间点，所以下一秒就会
  updated = false;
}

void loop() {
  
  microsEnd = micros(); // 获取当前微秒计时
  int timereach = (microsEnd - microsBegin)/1000000;  //将微秒转换成秒
  
  if(timereach > period && !updated){ // 每 30 分更新一次数据

    // make connection to server
    if(client.connect(server, 80)){
      Serial.print("connect to server, remote IP is: ");
      Serial.println(client.remoteIP());

      client.println("GET /v3/weather/weatherInfo?city=500100&key=6e4fcdb44e2ffd750176c6b76c372b09 HTTP/1.1");
      client.println("Host: restapi.amap.com");
      client.println("Connection: close");
      client.println();
      
    }else
      Serial.println("Connect to server was failed");

    microsBegin = micros();
    updated = true; // 有更新的信息需要显示
  }

  if(client.available() && updated){
    client.findUntil("{", "{"); // 找到读取起始位置
    String strMessage = client.readStringUntil("}"); // 读取字串直到
    int offsetTemp = strMessage.indexOf("temperature");
    int offsetHmty = strMessage.indexOf("humidity");
    Serial.println(strMessage);
    Serial.println(strMessage.substring(offsetHmty,offsetHmty+13));
    
    lcd.setCursor(0,0); // 光标移到 0 行, 0 列
    lcd.print("Temperature: ");
    lcd.print(strMessage.substring(offsetTemp+14,offsetTemp+16));

    lcd.setCursor(0,1); // 光标移到 1 行, 0 列
    lcd.print("Humidity: ");
    lcd.print(strMessage.substring(offsetHmty+11,offsetHmty+13));    

    updated = false; //更新信息已完成显示
  }
  
  delay(2000);
}
