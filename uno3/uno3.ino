#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SS_PIN 10
#define RST_PIN 9
#define sensor 2
Servo myservo1, myservo2;
#define GREEN_LED 6
#define RED_LED 4
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Wire.begin(10);                /* join i2c bus with address 10 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
//  
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
  
  lcd.init();       // khai báo sử dụng LCD
  lcd.begin(16, 2);
  lcd.backlight();
  int l;
  Serial.println("Hệ thống cửa tự động");
  lcd.clear();
  lcd.setCursor(1,0);       // Cột 1 hàng 1 
  lcd.print(" HE THONG CUA ");
  lcd.setCursor(2,1);         // cột 2 hàng 2
  lcd.print(" THONG MINH ");
  
  
  
}
void loop() 
{
  Serial.print("Gia tri cam bien:");
  if (digitalRead(sensor) == 0)
  {
    digitalWrite(GREEN_LED, HIGH); 
    delay(3000);
  }
  else{
    digitalWrite(GREEN_LED, LOW);
  }
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "3C 87 F6 22")
  {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("  Open door ");
    lcd.setCursor(2,1);
    lcd.print(" cho nguoi vao ");
    digitalWrite(RED_LED,HIGH);
      delay(500);
    Serial.println("Opendoor");
    Serial.println();
    digitalWrite(1,1);
   { 
      myservo1.write(0);
      delay(1000);
      myservo2.write(100);
      delay(3000);
      }
      
    if(digitalRead(sensor)==0)
    { 
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("  Open door ");
      lcd.setCursor(2,1);
      lcd.print(" man go home");
      Serial.println("man go home");
      myservo1.write(0);
      delay(1000);
      myservo2.write(100);
      delay(1000);

      }
   if(digitalRead(sensor)==1)
      {
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("  close door");
      lcd.setCursor(2,1);
      lcd.print(" man go out");
      Serial.println("closedoor");
      myservo2.write(0);
      delay(1000);
      myservo1.write(120);
      delay(1000);

     }
    }
else
  {
      Serial.println("!Authorized access");
    Serial.println();
    digitalWrite(1,0);
        }
    if (content.substring(1) == "14 EE FE 2B")
  {
        digitalWrite(RED_LED,LOW);
      delay(500);
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(1,1);
  }
  
 
}
// su kien mo cua


 void receiveEvent(int howMany) {
    String status ="";            //bat tat den khi nhan duoc tin hieu mo cua tu 8266
    while(0 < Wire.available()){
    char c = Wire.read(); 
    status+=c;
  }
  
  if(status.equals("open-door")){

      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("  Open door ");
      lcd.setCursor(2,1);
      lcd.print(" cho nguoi vao ");
      digitalWrite(RED_LED,HIGH);
      delay(500);
      Serial.println("Open door");
      Serial.println();
      digitalWrite(1,1);
      myservo1.write(0);
      delay(1000);
      myservo2.write(100);
      delay(3000);
      }
       
}
  


// function that executes whenever data is requested from master
void requestEvent() {
  Wire.print("hello from uno3");
 } 
