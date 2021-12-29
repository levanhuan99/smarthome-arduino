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
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "OK");
  });

    server.on("/light1-on", HTTP_GET, [] (AsyncWebServerRequest *request) {  //api bat den
        Serial.println("Above for debugging!");
        Wire.beginTransmission(8); /* begin with device address 8 */
        Serial.println("under for debugging!");
        Wire.write("1-on");  /* sends id cua thiet bi can bat  string */
        Serial.println("middle for debugging!");
        Wire.endTransmission();    /* stop transmitting */
        Serial.println("end for debugging!");
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

  //lay nhiet do, do am/tran thai den
     server.on("/get-all-status", HTTP_GET, [] (AsyncWebServerRequest *request) { 
      Wire.requestFrom(8, 50); /* request & read data of size 50 from slave */
      String result = "";
      while(Wire.available()){
        char c = Wire.read();
        result+= c;
       
      } 
      Wire.requestFrom(9, 50); /* request & read data of size 50 from slave */
      while(Wire.available()){
        char c1 = Wire.read();
        result+= c1;
       
      } 
     Serial.print(String(result));
     request->send(200, "text/plain", result);

  });

//dieu khien quat
  server.on("/fan-1-on", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-1-on");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });
    server.on("/fan-1-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-1-off");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });
    server.on("/fan-2-on", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-2-on");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });
  
  server.on("/fan-2-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-2-off");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });
  server.on("/fan-3-on", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-3-on");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });
    server.on("/fan-3-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-3-off");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });
    server.on("/fan-4-on", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-4-on");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });
  
  server.on("/fan-4-off", HTTP_GET, [] (AsyncWebServerRequest *request) { //api tat den 
        Serial.print("1");
        Wire.beginTransmission(9); /* begin with device address 9 */
         Serial.print("2");
        Wire.write("fan-4-off");  /* sends id cua thiet bi can bat  string */
         Serial.print("3");
        Wire.endTransmission();    /* stop transmitting */
         Serial.print("4");
        //request->addHeader("Access-Control-Allow-Origin", "*");
        request->send(200, "text/plain", "OK");

  });

  
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server.begin();
  GetExternalIP();
}

void loop() {
}

void GetExternalIP()
{
  WiFiClient client;
  if (!client.connect("api.ipify.org", 80)) {
    Serial.println("Failed to connect with 'api.ipify.org' !");
  }
  else {
    int timeout = millis() + 5000;
    client.print("GET /?format=json HTTP/1.1\r\nHost: api.ipify.org\r\n\r\n");
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    int size;
    while ((size = client.available()) > 0) {
      uint8_t* msg = (uint8_t*)malloc(size);
      size = client.read(msg, size);
      Serial.write(msg, size);
      free(msg);
    }
  }
}
