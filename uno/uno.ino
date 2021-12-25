#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

//den va nut bam 1
const int buttonPin = 12;
const int ledPin = 13;
byte LED_state = LOW;       
byte lastButtonState = LOW;


//den va nut bam 2
const int buttonPin2 = 10;
const int ledPin2 = 11;
byte LED_state2 = LOW;       
byte lastButtonState2 = LOW;


//den va nut bam 3
const int buttonPin3 = 8;
const int ledPin3 = 9;
byte LED_state3 = LOW;       
byte lastButtonState3 = LOW;


//den va nut bam4
const int buttonPin4 = 6;
const int ledPin4 = 7;
byte LED_state4 = LOW;       
byte lastButtonState4 = LOW;

//cam bien va lcd
LiquidCrystal_I2C lcd(0x27,16,2);
const int DHTPIN = 2;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

//nhiet do va do am
String temp = "";
String hum = "";

void setup() {
   Serial.print("dmmmmmmm");
  
  //lcd va cam bien dht
  lcd.init();  
  lcd.backlight(); 
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.createChar(1, degree);
  dht.begin();  

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT); 
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin2, INPUT); 
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin3, INPUT); 
  pinMode(ledPin4, OUTPUT);
  pinMode(buttonPin4, INPUT); 
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */
}

void loop() {
    //btn1
    byte buttonState = digitalRead(buttonPin);

    if (buttonState != lastButtonState) { //nut bam bat tat den
      lastButtonState = buttonState;
      if (buttonState == LOW) {
        LED_state = (LED_state == HIGH) ? LOW: HIGH;  
        digitalWrite(ledPin, LED_state);
      }
    }

   //btn2
    byte buttonState2 = digitalRead(buttonPin2);

    if (buttonState2 != lastButtonState2) { //nut bam bat tat den
      lastButtonState2 = buttonState2;
      if (buttonState2 == LOW) {
        LED_state2 = (LED_state2 == HIGH) ? LOW: HIGH; 
        digitalWrite(ledPin2, LED_state2);
      }
    }
   //btn3
    byte buttonState3 = digitalRead(buttonPin3);

    if (buttonState3 != lastButtonState3) { //nut bam bat tat den
      lastButtonState3 = buttonState3;
      if (buttonState3 == LOW) {
        LED_state3 = (LED_state3 == HIGH) ? LOW: HIGH; 
        digitalWrite(ledPin3, LED_state3);
      }
    }
    //btn4
    byte buttonState4 = digitalRead(buttonPin4);

    if (buttonState4 != lastButtonState4) { //nut bam bat tat den
      lastButtonState4 = buttonState4;
      if (buttonState4 == LOW) {
        LED_state4 = (LED_state4 == HIGH) ? LOW: HIGH;  //toán tử so sánh
        digitalWrite(ledPin4, LED_state4);
      }
    }


    //cam bien va lcd
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(t) || isnan(h)) { 
  } 
  else {
    lcd.setCursor(10,0);
    lcd.print(round(t));
    temp = String(t, 2);
    lcd.print(" ");
    lcd.write(1);
    lcd.print("C");

    lcd.setCursor(10,1);
    lcd.print(round(h));
    hum = String(h, 2);
    lcd.print(" %");    
  }
}

// function that executes whenever data is received from master to change led status
void receiveEvent(int howMany) {
   Serial.println("start!");
  String status ="";            //bat tat den khi nhan duoc tin hieu tu 8266
  while(0 < Wire.available()){
    char c = Wire.read(); 
    status+=c;
  }
  Serial.println("param from 8266: "+status);
  if(status.equals("1-on")){
      LED_state = HIGH;
      digitalWrite(ledPin, HIGH);
  }else if(status.equals("1-off")){
      LED_state = LOW;
     digitalWrite(ledPin, LOW);
  } 
  else if(status.equals("2-on")){
      LED_state2 = HIGH;
     digitalWrite(ledPin2, HIGH);
  }else if(status.equals("2-off")){
      LED_state2 = LOW;
     digitalWrite(ledPin2, LOW);
  } 
  else if(status.equals("3-on")){
      LED_state3 = HIGH;
     digitalWrite(ledPin3, HIGH);
  }else if(status.equals("3-off")){
    LED_state3 = LOW;
     digitalWrite(ledPin3, LOW);
  } 
  else if(status.equals("4-on")){
     LED_state4 = HIGH;
     digitalWrite(ledPin4, HIGH);
  }else if(status.equals("4-off")){
    LED_state4 = LOW;
     digitalWrite(ledPin4, LOW);
     
  } 
  //open door door-1-open
//  else if(status.equals("door-1-open")){
//     digitalWrite(ledPin5, HIGH);         //TODO change ledPin to door
//  }else if(status.equals("4-off")){
//     digitalWrite(ledPin5, LOW);
//     
//  } 
}

// function that executes whenever data is requested from master
void requestEvent() {
 //String(LED_state)+","+String(LED_state2) +","+String(LED_state3)+","String(LED_state4)+"," +
   Wire.print(String(temp)+","+String(hum) +","+LED_state+","+LED_state2+","+LED_state3+","+LED_state4);

}
