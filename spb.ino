#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define led10 39
#define led20 42
#define led2 52
#define led1 48
#define led50 45

float money_insert = 0;
String currency = "leva";
int buttonLcdState = 1, buttonMoneyState = 1;
int lastButtonLcdState = 1, lastButtonMoneyState = 1;
//Servo moneyservo; 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 

void changeCurrency()
{
  String currencies[] = {"leva", "euro", "pounds"};
  static int presses = 1;
  lastButtonLcdState = buttonLcdState;
  buttonLcdState = digitalRead(6);

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
    lcd.print(money_insert);
  }
  else if(currency == "euro")
  {
    lcd.print(money_insert * 0.51);
  }
  else
  {
     lcd.print(money_insert * 0.43);
  }
}

void setup() {
  //moneyservo.attach(9);
  //moneyservo.write(70);

  lcd.init();
  lcd.backlight();
  
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

  pinMode(3, INPUT); 
  pinMode(6, INPUT); 

  lcd.setCursor(1, 0); 
  lcd.print("Current money:"); 
  lcd.setCursor(2, 1);
  lcd.print(money_insert);
  lcd.setCursor(9 , 1);
  lcd.print(currency);
  
  delay(1000);
}

void loop() 
{
  changeCurrency()
  printMoney();

  int valuefor2 = analogRead(A0);
  int valuefor1 = analogRead(A1);
  int valuefor50 = analogRead(A2);
  int valuefor20 = analogRead(A3);
  int valuefor10 = analogRead(A4);

  
  int value5 = analogRead(A8);
  int value10 = analogRead(A9);
  int value20 = analogRead(A10);
  int value30 = analogRead(A11);
  int value40 = analogRead(A12);

  /*Serial.println(value5);
  Serial.println(value10);
  Serial.println(value20);
  Serial.println(value30);
  Serial.println(value40);
  Serial.println();*/

  //Serial.println(valuefor1);
  //delay(5000);

  /*Serial.println("Button 3");
  Serial.println(digitalRead(3));   
  Serial.println("Button 7");
  Serial.println(digitalRead(6));  */  
  
  if(valuefor2 < 900)
  {
    money_insert += 2.0;
    Serial.println("2 leva");
    delay(250); 
  }
  
  else if(valuefor1 < 890)
  {
    money_insert += 1.0; 
    Serial.println("1 leva");
    delay(250); 
  }
  
  else if(valuefor50 < 900)
  {
    money_insert += 0.5;
    Serial.println("50 st");
    delay(250); 
  }
  
  else if(valuefor20 < 900)
  {
    money_insert += 0.2;
    Serial.println("20 st");
    delay(250); 
  }

  else if(valuefor10 < 900)
  {
    money_insert += 0.1;
    Serial.println("10 st");
    delay(250); 
  }

  
  int degree;
  //delay(1000);
  
 /* for (degree = 0; degree <= 70; degree += 1) 
  { 
    moneyservo.write(degree);           
    delay(15);                       
  }

  delay(3000);
  
  for (degree = 70; degree >=-0; degree -= 1) 
  {
    moneyservo.write(degree);            
    delay(15);                    
  }*/

  //delay(1000);
}
