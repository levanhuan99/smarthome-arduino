#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
const char* ssid = "TP-Link"; //Write your SSID
const char* password = "34219317";   //Write your password
 char* input_parameter = "id";   //1: led1, 2:led2, 3: led3

AsyncWebServer server(80);
const int D1 = 5;
const int D2 = 4;
void setup() {
 Serial.begin(9600); /* begin serial for debug */
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "OK");
  });

    server.on("/light1-on", HTTP_GET, [] (AsyncWebServerRequest *request) {  //api bat den
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("1-on");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */
        request->send(200, "text/plain", "OK");


  });

    server.on("/light1-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("1-off");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */

        request->send(200, "text/plain", "OK");

  });

    server.on("/light2-on", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("2-on");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */
        request->send(200, "text/plain", "OK");

  });

    server.on("/light2-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("2-off");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */
        request->send(200, "text/plain", "OK");

  });

     server.on("/light3-on", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("3-on");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */
        request->send(200, "text/plain", "OK");

  });

  
     server.on("/light3-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("3-off");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */
        request->send(200, "text/plain", "OK");

  });

    
     server.on("/light4-on", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("4-on");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */
        request->send(200, "text/plain", "OK");

  });

    
     server.on("/light4-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Wire.beginTransmission(8); /* begin with device address 8 */
        Wire.write("4-off");  /* sends id cua thiet bi can bat  string */
        Wire.endTransmission();    /* stop transmitting */
        request->send(200, "text/plain", "OK");

  });

  //lay nhiet do, do am
     server.on("/temp", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
      Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
      String result = "";
      while(Wire.available()){
        char c = Wire.read();
        result+= c;
       
      }
      Serial.print(String(result));
    request->send(200, "text/plain", result);

  });
  server.begin();
}

void loop() {

}
