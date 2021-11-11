#include <Wire.h>

int led1 = 11;
int led2 = 10;
int led3 = 9;
int led4 = 8;

int fan1 = 5;
int fan2 = 4;
int fan3 = 3;
int fan4 = 2;

//
int relay1 = 7;
void setup()
{
  Wire.begin(9);                /* join i2c bus with address 9 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  pinMode(fan3,OUTPUT);
  pinMode(fan4,OUTPUT);
  pinMode(relay1,OUTPUT); 
  }
  String voice;
 void loop()
 {
  if (Serial.available()>0)
  {
    voice="";
    delay(2);
    
    voice=Serial.readString();
    delay(2);
    Serial.print(voice+'\n');
    }
  
  if(voice.equals("bật đèn 1"))
  {
    digitalWrite(led1,HIGH);
    }
  if(voice.equals("tắt đèn 1"))
   {
    digitalWrite(led1,LOW);
    }

  if(voice.equals("bật đèn 2"))
  {
    digitalWrite(led2,HIGH);
    }
  if(voice.equals("tắt đèn 2"))
   {
    digitalWrite(led2,LOW);
    }

  if(voice.equals("bật đèn 3"))
  {
    digitalWrite(led3,HIGH);
    }
  if(voice.equals("tắt đèn 3"))
   {
    digitalWrite(led3,LOW);
    }

  if(voice.equals("bật đèn 4"))
  {
    digitalWrite(led4,HIGH);
    }
  if(voice.equals("tắt đèn 4"))
   {
    digitalWrite(led4,LOW);
    }
    
   if(voice.equals("bật quạt 1"))
  {
    digitalWrite(fan1,HIGH);
    }
  if(voice.equals("tắt quạt 1"))
   {
    digitalWrite(fan1,LOW);
    }

  if(voice.equals("bật quạt 2"))
  {
    digitalWrite(fan2,HIGH);
    }
  if(voice.equals("tắt quạt 2"))
   {
    digitalWrite(fan2,LOW);
    }

  if(voice.equals("bật quạt 3"))
  {
    digitalWrite(fan3,HIGH);
    }
  if(voice.equals("tắt quạt 3"))
   {
    digitalWrite(fan3,LOW);
    }

  if(voice.equals("bật quạt 4"))
  {
    digitalWrite(fan4,HIGH);
    }
  if(voice.equals("tắt quạt 4"))
   {
    digitalWrite(fan4,LOW);
    }


   if(voice.equals("tắt hết")){
    digitalWrite(fan4,LOW);
    digitalWrite(fan3,LOW);
    digitalWrite(fan2,LOW);
    digitalWrite(fan1,LOW);

    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
   }
   if(voice.equals("bật hết")){
    digitalWrite(fan4,HIGH);
    digitalWrite(fan3,HIGH);
    digitalWrite(fan2,HIGH);
    digitalWrite(fan1,HIGH);

    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
   }
   
  if(voice.equals("bật đèn"))
  {
    digitalWrite(relay1,HIGH);
    }
  if(voice.equals("Tắt đèn") || voice.equals("tắt đèn") || voice.equals("Tắt Đèn")
  )
   {
    digitalWrite(relay1,LOW);
    }
 }

 void receiveEvent(int howMany) {
    String status ="";            //bat tat den khi nhan duoc tin hieu tu 8266
  while(0 < Wire.available()){
    char c = Wire.read(); 
    status+=c;
  }
  
  if(status.equals("fan-4-on")){
      digitalWrite(fan4, HIGH);
  }else if(status.equals("fan-4-off")){
     digitalWrite(fan4, LOW);
  } 
  
 }

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.print("hello from uno2");

} 
