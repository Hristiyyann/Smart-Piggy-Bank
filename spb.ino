#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define led10 53
#define led20 51
#define led2 52
#define led1 50
#define led50 48

Servo moneyservo; 

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 

void setup() {
  moneyservo.attach(9);
  moneyservo.write(0);
  
  Serial.begin(9600);
  pinMode(led10, OUTPUT); 
  digitalWrite(led10, HIGH);
  
  pinMode(led20, OUTPUT); 
  digitalWrite(led20, HIGH);

  pinMode(led50, OUTPUT); 
  digitalWrite(led50, HIGH);

  pinMode(led1, OUTPUT); 
  digitalWrite(led1, HIGH);
  
  pinMode(led2, OUTPUT); 
  digitalWrite(led2, HIGH);
  delay(1000);
}

void loop() {

  int valuefor2 = analogRead(A0);
  int valuefor1 = analogRead(A1);
  int valuefor50 = analogRead(A2);
  int valuefor20 = analogRead(A3);
  int valuefor10 = analogRead(A4);
  
  if(valuefor2 < 900)
  {
    Serial.println("2 leva");
    delay(250); 
  }
  
  else if(valuefor1 < 900)
  {
    Serial.println("1 leva");
    delay(250); 
  }
  
  else if(valuefor50 < 900)
  {
    Serial.println("50 st");
    delay(250); 
  }
  
  else if(valuefor20 < 900)
  {
    Serial.println("20 st");
    delay(250); 
  }

  else if(valuefor10 < 900)
  {
    Serial.println("10 st");
    delay(250); 
  }
}
