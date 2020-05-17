/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "Tenda_Cyberspace_2.4G";
const char* password = "1980jian";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.0.145:1880/get-sensor";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

String responseJson;
float responseJsonArr[3];

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password); // 用ssid, 和　password 启动wifi
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { // 检测 wifi 是否成功启动
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP()); //WiFi.localIP()方法返回获取IP地址
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
              
      responseJson = httpGETRequest(serverName);
      Serial.println(responseJson);
      JSONVar myObject = JSON.parse(responseJson); //JSON.parse()方法将Json格式字符串转换成JSONVar对象
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);
    
      // myObject.keys() can be used to get an array of all the keys in the object
      JSONVar keys = myObject.keys(); // keys() 方法生成键值列表，这个列表还是JsonVar类型
    
      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]]; // JSONVar 对象可以用key值来索引value值
        Serial.print(keys[i]);
        Serial.print(" = ");
        Serial.println(value);
        responseJsonArr[i] = double(value); //将JsonVar类型强制转换成 double
      }
      Serial.print("1 = ");
      Serial.println(responseJsonArr[0]);
      Serial.print("2 = ");
      Serial.println(responseJsonArr[1]);
      Serial.print("3 = ");
      Serial.println(responseJsonArr[2]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
