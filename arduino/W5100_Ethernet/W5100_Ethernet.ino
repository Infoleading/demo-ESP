#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // mac地址可以自定，保证不与网段内其它设备相同即可
byte ip[] = {192, 168, 0, 10};
EthernetClient client;
EthernetServer server(80);
char url[] = "restapi.amap.com";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  /* 初始化方式一：自动获取IP地址，返回 bool类型，
  //if(Ethernet.begin(mac)){ //最小参数，自动获取IP地址
    Serial.println(Ethernet.localIP());
  }else{
    Serial.println("Could not connect network");
  }
  */

  // 初始化方式二：指定 IP 地址
  Ethernet.begin(mac,ip); //指定IP地址
  Serial.println(Ethernet.localIP());

  // 启动服务器
  server.begin();

  // 访问网站
  visiteWeb();
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
 * 模拟浏览器访问网站，获取返回信息
 */
void visiteWeb(){
  // 启动浏览器
  if(client.connect(url,80)){
    client.println("GET /v3/weather/weatherInfo?city=500100&key=6e4fcdb44e2ffd750176c6b76c372b09 http1.1");
    while(client.connected()){
      if(client.available()){
        String description = client.readString();
        Serial.println(description);
      }
    }
    client.stop();
  }else
    Serial.println("connect failed");
}
