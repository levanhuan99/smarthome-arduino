#include <Wire.h>

int fan1 = 5;
int fan2 = 4;
int fan3 = 3;
int fan4 = 2;
byte lastButtonState1 = LOW;
byte lastButtonState2 = LOW;
byte lastButtonState3 = LOW;
byte lastButtonState4 = LOW;

//bong den 220v
int relay1 = 7;

//cam bien khi gas
int buzzer = 10;
int smokeA0 = A3;
// Your threshold value
int sensorThres = 400;

//joystick
int enA = 9;
int in1 = 11;
int in2 = 12;
int speedmotor = 0;

void setup()
{
  Wire.begin(9);                /* join i2c bus with address 9 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  pinMode(fan3,OUTPUT);
  pinMode(fan4,OUTPUT);
  pinMode(relay1,OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
}
  
 String voice;
  
 void loop()
 {
    controlJoyStick();
  if (Serial.available()>0){
    voice="";
    delay(100);
    
    voice=Serial.readString();
    delay(100);
    Serial.print(voice+'\n');
  }
  if(voice.equals("bật quạt phòng khách") || ( voice.indexOf("bật") >0 && voice.indexOf("khách") >0) ){
    passValueToSingleDeviceStatus(lastButtonState1,HIGH);
    digitalWrite(fan1,HIGH);
  }
  if(voice.equals("tắt quạt phòng khách") || ( voice.indexOf("bật") >0 && voice.indexOf("khách") >0) ){
    passValueToSingleDeviceStatus(lastButtonState1,LOW);
    digitalWrite(fan1,LOW);
  }

  if(voice.equals("bật quạt phòng ngủ 1") || voice.equals("bật quạt phòng ngủ một") || ( voice.indexOf("bật") >0 && voice.indexOf("1") >0)){
    passValueToSingleDeviceStatus(lastButtonState2,HIGH);
    digitalWrite(fan2,HIGH);
  }
  if(voice.equals("tắt quạt phòng ngủ 1") || voice.equals("tắt quạt phòng ngủ một") || ( voice.indexOf("tắt") >0 && voice.indexOf("1") >0) ){
    passValueToSingleDeviceStatus(lastButtonState2,LOW);
    digitalWrite(fan2,LOW);
  }

  if(voice.equals("bật quạt phòng ngủ 2") || voice.equals("bật quạt phòng ngủ hai") || ( voice.indexOf("bật") >0 && voice.indexOf("2") >0)){
    passValueToSingleDeviceStatus(lastButtonState3,HIGH);
    digitalWrite(fan3,HIGH);
    }
  if(voice.equals("tắt quạt phòng ngủ 2") || voice.equals("tắt quạt phòng ngủ hai")  || ( voice.indexOf("tắt") >0 && voice.indexOf("2") >0)){
    passValueToSingleDeviceStatus(lastButtonState3,LOW);
    digitalWrite(fan3,LOW);
  }

  if(voice.equals("bật quạt phòng bếp") || ( voice.indexOf("bật") >0 && voice.indexOf("bếp") >0)){
    passValueToSingleDeviceStatus(lastButtonState4,HIGH);
    digitalWrite(fan4,HIGH);
  }
  if(voice.equals("tắt quạt phòng bếp") || ( voice.indexOf("tắt") >0 && voice.indexOf("bếp") >0)){
    passValueToSingleDeviceStatus(lastButtonState4,LOW);
    digitalWrite(fan4,LOW);
  }


   if(voice.equals("tắt hết quạt")){
    passValueToAllFanStatus(LOW);
    digitalWrite(fan4,LOW);
    digitalWrite(fan3,LOW);
    digitalWrite(fan2,LOW);
    digitalWrite(fan1,LOW);
    digitalWrite(relay1,LOW);
   }
   if(voice.equals("bật hết quạt")){
    passValueToAllFanStatus(HIGH);
    digitalWrite(fan4,HIGH);
    digitalWrite(fan3,HIGH);
    digitalWrite(fan2,HIGH);
    digitalWrite(fan1,HIGH);
    digitalWrite(relay1,HIGH);
   }
   
  if(voice.equals("bật đèn")){
    digitalWrite(relay1,HIGH);
    }
  if(voice.equals("Tắt đèn") || voice.equals("tắt đèn") || voice.equals("Tắt Đèn")){
    digitalWrite(relay1,LOW);
  }

// kiem tra cam bien khi gas va thong bao coi
  checkGasSensorAndShowBuzzer();

  
 }
void controlJoyStick(){
      int xAxis = analogRead(A0);
      int yAxis = analogRead(A1);

      //y-Axis
      if(yAxis <470){
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        speedmotor = map(yAxis, 470, 0, 0, 225);
      }
      else if(yAxis > 550){
        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        speedmotor = map(yAxis, 550, 1023, 0, 225);
      }
      //
      else{
        speedmotor = 0;
      }

      
      //X-Axis
      if(xAxis < 470){
        int xMapped = map(xAxis, 470, 0, 0, 100);
        speedmotor = speedmotor - xMapped;
        if(speedmotor < 0){
          speedmotor = 0;
        }
      }

       if(xAxis > 550){
        int xMapped = map(xAxis, 550, 1023, 0, 100);
        speedmotor = speedmotor + xMapped;
        if(speedmotor > 255){
          speedmotor = 255;
        }
      }
      if(speedmotor < 70){
        speedmotor = 0;
      }
      analogWrite(enA, speedmotor);
}
void checkGasSensorAndShowBuzzer(){
  int analogSensor = analogRead(smokeA0);
//  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres){
    
    tone(buzzer, 1000, 200);
    delay(2000);
  }
  else  {
     noTone(buzzer);
  }

}

void passValueToAllFanStatus(byte status){
   lastButtonState1 = status;
   lastButtonState2 = status;
   lastButtonState3 = status;
   lastButtonState4 = status;
}
void passValueToSingleDeviceStatus(byte device, byte status){
  device  = status;
}

void receiveEvent(int howMany) {
    String status ="";            //bat tat den khi nhan duoc tin hieu tu 8266
  while(0 < Wire.available()){
    char c = Wire.read(); 
    status+=c;
  }
  if(status.equals("fan-1-on")){
    passValueToSingleDeviceStatus(lastButtonState1,HIGH);
    digitalWrite(fan1, HIGH);
  }else if(status.equals("fan-1-off")){
    passValueToSingleDeviceStatus(lastButtonState1,LOW);
    digitalWrite(fan1, LOW);
  } 
  if(status.equals("fan-2-on")){
    passValueToSingleDeviceStatus(lastButtonState2,HIGH);
    digitalWrite(fan2, HIGH);
  }else if(status.equals("fan-2-off")){
    passValueToSingleDeviceStatus(lastButtonState2,LOW);
    digitalWrite(fan2, LOW);
  } 
  if(status.equals("fan-3-on")){
    passValueToSingleDeviceStatus(lastButtonState3,HIGH);
    digitalWrite(fan3, HIGH);
  }else if(status.equals("fan-3-off")){
    passValueToSingleDeviceStatus(lastButtonState3,LOW);
    digitalWrite(fan3, LOW);
  } 
  if(status.equals("fan-4-on")){
    passValueToSingleDeviceStatus(lastButtonState4,HIGH);
    digitalWrite(fan4, HIGH);
  }else if(status.equals("fan-4-off")){
    passValueToSingleDeviceStatus(lastButtonState4,LOW);
    digitalWrite(fan4, LOW);
  } 
  
}

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.print(String(",")+lastButtonState1+","+lastButtonState2+","+lastButtonState3+","+lastButtonState4);
}
