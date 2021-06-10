#include <LiquidCrystal.h>
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int relay=5;
int fan=3;
char t;

void setup() 
{
   pinMode(relay,OUTPUT);
   pinMode(fan,OUTPUT);
   Serial.begin(9600);
    lcd.begin(16, 2);
   lcd.setCursor(0, 0);
   lcd.print("Voice Acti. Home");
}

void loop() 
{
 
   if(Serial.available())
{
  t = Serial.read();
  //Serial.print("Bluetooth Data =");
  Serial.print(t);
  //Serial.println("");

  lcd.setCursor(0, 0);
  lcd.print("Voice Acti. Home");
  
  if (t=='a')
  {
    digitalWrite(relay,1);
    lcd.setCursor(0, 1);
    lcd.print("L= ON  ");
    Serial.println("Light ON");
    
  }
  else if (t=='b')
  {
     digitalWrite(relay,0);
     lcd.setCursor(0, 1);
     lcd.print("L= OFF ");
     Serial.println("Light OFF");
  }

 else  if (t=='x')
  { 
    digitalWrite(fan,1);
    lcd.setCursor(7, 1);
    lcd.print("M= ON    ");
    Serial.println("Motor ON");
  }
  else if (t=='Z')
  {
    digitalWrite(fan,0);
    lcd.setCursor(7, 1);
    lcd.print("M= OFF   ");
    Serial.println("Motor OFF   ");
  }

   if (t=='1')
  {
    analogWrite(fan,63);
    lcd.setCursor(7, 1);
    lcd.print("M=Level 1  ");
    Serial.println("Motor Speed = Level 1");
  }
  else if (t=='3')
  {
    analogWrite(fan,126);
    lcd.setCursor(7, 1);
    lcd.print("M=Level 2");
    Serial.println("Motor Speed = Level 2");
  }
  else if (t=='5')
  {
    analogWrite(fan,189);
    lcd.setCursor(7, 1);
    lcd.print("M=Level 3");
    Serial.println("Motor Speed = Level 3");
  }
  else if (t=='7')
  {
    analogWrite(fan,255);
    lcd.setCursor(7, 1);
    lcd.print("M=Level 4");
    Serial.println("Motor Speed = Level 4");
   
  }  
}

}
