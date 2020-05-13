#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // mac地址可以自定，保证不与网段内其它设备相同即可
byte ip[] = {192, 168, 0, 10};
EthernetClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  if(Ethernet.begin(mac)){ //最小参数，自动获取IP地址
    Serial.print("Ip address: ");
    Serial.println(Ethernet.localIP());
  }else{
    Serial.println("Could not connect network");
  }

  if(client.connect("restapi.amap.com",80)){
    client.println("GET /v3/weather/weatherInfo?city=500100&key=6e4fcdb44e2ffd750176c6b76c372b09,uk HTTP/1.1");
    client.println();
    while(client.connected()){
      while(client.available())
        Serial.write(client.read());
    }
    client.stop();
  }else
    Serial.println("connect failed");
}

void loop() {
  // put your main code here, to run repeatedly:
}
