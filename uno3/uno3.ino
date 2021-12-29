#include <Servo.h>


const int rainSensor = 9;
const int lightSensor = 10;
const int servoPinCua = 7;  
Servo motorPhoi;

void setup() {

  Serial.begin(9600);
  motorPhoi.attach(servoPinCua);
  pinMode(rainSensor,INPUT);
  pinMode(lightSensor,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(rainSensor)); //0 : khong mua, 1:mua
    Serial.println(digitalRead(lightSensor));//1 khong co anh sang, 0: co anh sang
    delay(5000);
if(digitalRead(rainSensor)==0 && digitalRead(lightSensor)==0){
  Serial.println(" mo day phoi ");

    motorPhoi.write(180);
}else{
  
  Serial.println(" k mo day phoi");
  motorPhoi.write(0);
}
}
