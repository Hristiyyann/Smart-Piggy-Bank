#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define led10 39
#define led20 42
#define led2 52
#define led1 48
#define led50 45
#define lcdButton 6
#define servoButton 3


float moneyInsert = 0;
String currency = "leva";
int buttonLcdState = 1, buttonMoneyState = 1;
int lastButtonLcdState = 1, lastButtonMoneyState = 1;
Servo moneyServo; 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 

void servoMoving()
{
  int countCoveredLDR = 0;
  int paperMoneyValue5 = analogRead(A12);
  int paperMoneyValue10 = analogRead(A11);
  int paperMoneyValue20 = analogRead(A10);
  int paperMoneyValue50 = analogRead(A9);
  int paperMoneyValue100 = analogRead(A8);

  if(paperMoneyValue5 < 830)
  {
    countCoveredLDR++;
  }
  if(paperMoneyValue10 < 900)
  {
    countCoveredLDR++;
  }
  if(paperMoneyValue20 < 850)
  {
    countCoveredLDR++;
  }
  if(paperMoneyValue50 < 850)
  {
    countCoveredLDR++;
  }
  if(paperMoneyValue100 < 800)
  {
    countCoveredLDR++;
  }
  
  Serial.println("total");
  Serial.println(countCoveredLDR);
  
  switch(countCoveredLDR)
  {
    case 1: moneyInsert += 5; break;
    case 2: moneyInsert += 10; break;
    case 3: moneyInsert += 20; break;
    case 4: moneyInsert += 50; break;
    case 5: moneyInsert += 100; break;
  }

  Serial.println("money");
  Serial.println(moneyInsert);
  
  Serial.println(paperMoneyValue5);
  Serial.println(paperMoneyValue10);
  Serial.println(paperMoneyValue20);
  Serial.println(paperMoneyValue50);
  Serial.println(paperMoneyValue100);
  Serial.println();
  
  int degree;
  delay(1000);

  for (degree = 70; degree >=-0; degree -= 1) 
  {
    moneyServo.write(degree);            
    delay(15);                    
  }

  delay(500);
  
  for (degree = 0; degree <= 70; degree += 1) 
  { 
     moneyServo.write(degree);           
     delay(15);                       
  }
}

int readPaperMoney()
{
  lastButtonMoneyState = buttonMoneyState;
  buttonMoneyState = digitalRead(servoButton);

  if(lastButtonMoneyState != buttonMoneyState && buttonMoneyState == LOW)
  {
      return 1;
  }

  return 0;
}

void changeCurrency()
{
  String currencies[] = {"leva", "euro", "pounds"};
  static int presses = 1;
  lastButtonLcdState = buttonLcdState;
  buttonLcdState = digitalRead(lcdButton);

  if(lastButtonLcdState != buttonLcdState && buttonLcdState == LOW)
  {
    lcd.setCursor(8, 1);
    
    for(int n = 8; n < 16; n++) 
    {
       lcd.print(" ");
    }
    
    if(presses == 3)
    {
      presses = 0;
      currency = currencies[presses];
    }
     
    if(presses == 1)
    {
      currency = currencies[presses];
    }

    else if(presses == 2)
    {
       currency = currencies[presses];
    }

    else
    {
       currency = currencies[presses];
    }

    lcd.setCursor(9, 1);
    lcd.print(currency);
    Serial.println(presses);

    presses++;
  }
}

void printMoney()
{
  lcd.setCursor(0, 1);
  for(int n = 0; n < 8; n++) 
  {
     lcd.print(" ");
  }
  lcd.setCursor(2, 1);
  
  if(currency == "leva")
  {
    lcd.print(moneyInsert);
  }
  else if(currency == "euro")
  {
    lcd.print(moneyInsert * 0.51);
  }
  else
  {
     lcd.print(moneyInsert * 0.43);
  }
}

void setup() {
  moneyServo.attach(9);
  moneyServo.write(70);

  lcd.init();
  lcd.backlight();
  
  Serial.begin(9600);
  pinMode(led10, OUTPUT); 
  pinMode(led20, OUTPUT); 
  pinMode(led50, OUTPUT); 
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT);
  
  digitalWrite(led10, HIGH);
  digitalWrite(led20, HIGH);
  digitalWrite(led50, HIGH); 
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  pinMode(servoButton, INPUT); 
  pinMode(lcdButton, INPUT); 
  pinMode(12, OUTPUT);
   digitalWrite(12, HIGH);

  lcd.setCursor(1, 0); 
  lcd.print("Current money:"); 
  lcd.setCursor(2, 1);
  lcd.print(moneyInsert);
  lcd.setCursor(9 , 1);
  lcd.print(currency);
  
  delay(1000);
}

void loop() 
{
  changeCurrency();
  printMoney();
  if(readPaperMoney() == 1)
  {
    servoMoving();
  }

  int coinValueFor2 = analogRead(A0);
  int coinValueFor1 = analogRead(A1);
  int coinValueFor50 = analogRead(A2);
  int coincoinValueFor20 = analogRead(A3);
  int coinValueFor10 = analogRead(A4);

  if(coinValueFor2 < 890)
  {
    moneyInsert += 2.0;
    Serial.println("2 leva");
    Serial.println(coinValueFor2);
    delay(250); 
  }
  
  else if(coinValueFor1 < 880)
  {
    moneyInsert += 1.0; 
    Serial.println("1 leva");
    Serial.println(coinValueFor1);
    delay(250); 
  }
  
  else if(coinValueFor50 < 900)
  {
    moneyInsert += 0.5;
    Serial.println("50 st");
    delay(250); 
  }
  
  else if(coincoinValueFor20 < 900)
  {
    moneyInsert += 0.2;
    Serial.println("20 st");
    delay(250); 
  }

  else if(coinValueFor10 < 900)
  {
    moneyInsert += 0.1;
    Serial.println("10 st");
    delay(250); 
  }

  //delay(1000);
}
