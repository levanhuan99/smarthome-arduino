#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <Servo.h>

// RFID
#include <SPI.h>
#include <MFRC522.h>
const int RST_PIN=16;         // Configurable, see typical pin layout above
const int SS_PIN = 15;         // Configurable, see typical pin layout above

//sensor 
const int sensor = 9;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


const char* ssid = "TP-Link"; //Write your SSID
const char* password = "34219317";   //Write your password
char* input_parameter = "id";   //1: led1, 2:led2, 3: led3

/* Servo */
const int servoPinCua = 0;     // D3: chan servo cua
/* Create Servo Object */
Servo servoCua;

AsyncWebServer server(80);
int angle ;


//const char* PARAM_MESSAGE = "current_user_name";

void setup() {
 Serial.begin(115200); /* begin serial for debug */
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

 servoCua.attach(servoPinCua);
 pinMode(sensor,INPUT);
  
 // the tu
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));


 

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    
    request->send(200, "text/plain", "OK");
  });


  server.on("/open-door", HTTP_GET, [] (AsyncWebServerRequest *request) { 
        Serial.println("incoming request!");
        angle=100;
        servoCua.write(angle);
        request->send(200, "text/plain", "OK");

  });
  server.begin();
  GetExternalIP();
}

void loop() {
// Look for new cards
 
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    servoCua.write(angle);
     return;
  }
 
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)  {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "3C 87 F6 22"  || content.substring(1) ==  "03 C2 C0 21") { 
      
        Serial.println("access authorize!");
        angle = 100;
        servoCua.write(angle);
        delay(1000);

        

      //kiem tra cam bien
      
       if(digitalRead(sensor)== 0) { //
        Serial.print("Message : GIU VI TRI");
        servoCua.write(angle);

        
       }
     
       if(digitalRead(sensor)== 1) { // 
          Serial.print("Message :  TRO VE VI TRI BAN DAU");
          delay(1000);
          angle = 0;
          servoCua.write(angle);
    
       } 
       Serial.println("sensor value: "+ String(digitalRead(sensor)));
    } else{
          
        Serial.println("!Authorized access");
        Serial.println();

       
    }
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
