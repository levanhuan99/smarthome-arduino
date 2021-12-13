#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SS_PIN 10
#define RST_PIN 9
#define sensor 2
Servo myservo1, myservo2;
#define GREEN_LED 6
#define RED_LED 4

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int data ;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(1,OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  myservo1.attach(7);
  myservo2.attach(8);
  
//  lcd.init();       // khai báo sử dụng LCD
//  lcd.begin(16, 2);
//  lcd.backlight();
//  int l;
//  Serial.println("he thong tu dong");
//  lcd.clear();
//  lcd.setCursor(1,0);       // Cột 1 hàng 1 
//  lcd.print(" HE THONG CUA ");
//  lcd.setCursor(2,1);         // cột 2 hàng 2
//  lcd.print(" THONG MINH ");
  
  
  
}
void loop() 
{

  data = Serial.read();

  if(data != -1){
        digitalWrite(RED_LED,HIGH);
        Serial.println("data from 8266 is:     "+String(data));
//        myservo1.write(0);
//        delay(1000);
//        myservo2.write(100);
        delay(3000);
       
  }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
        myservo2.write(0);
        delay(0);
        myservo1.write(180);
        delay(0);
        
    return;
  } 
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    
      return;
  }

  //Show UID on serial monitor
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
    if (content.substring(1) == "3C 87 F6 22") {
        digitalWrite(RED_LED,HIGH);
        myservo1.write(0);
        delay(1000);
        myservo2.write(100);
        delay(3000);
        
        
        if(digitalRead(sensor)==0) { 
          myservo1.write(0);
          delay(1000);
          myservo2.write(100);
          delay(1000);
        
       }
       if(digitalRead(sensor)==1) {
          myservo2.write(0);
          delay(1000);
          myservo1.write(180);
          delay(1000);
    
       }
       digitalWrite(RED_LED,LOW);
    } else{
        Serial.println("!Authorized access");
        Serial.println();
        digitalWrite(1,0);
       
     }

  }
