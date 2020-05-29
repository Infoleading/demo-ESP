/*
 * Testing read the file that upload in SPIFFS
 * you should upload test.txt in advance
 */

#include "SPIFFS.h"
 
void setup() {
  Serial.begin(115200);
  Serial.println("setup is running");
  
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //  open file for writing
  File file = SPIFFS.open("/test.txt", FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if (!file.print("This is content of file test.txt in SPIFFS.\n")){
    Serial.println("Failed to write file");
    return;
  }
  file.close();

  //open file for appending
  File file3 = SPIFFS.open("/test.txt", FILE_APPEND);
  if(!file3){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(!file3.println("Append a new line to file")){
    Serial.println("Failed to append file");
    return;
  }
  file3.close();

  // open file for reading
  File file2 = SPIFFS.open("/test.txt");
  if(!file2){
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.println("File Content:");
  while(file2.available()){
    Serial.write(file2.read());
  }
  file2.close();  
  
}

 
void loop() {

}
