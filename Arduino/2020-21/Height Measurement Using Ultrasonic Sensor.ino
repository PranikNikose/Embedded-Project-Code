#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
#define trigPin 8
#define echoPin 9
long Duration,Distance,abc, Height;

void setup() {
 Serial.begin(9600);
 lcd.begin(16,2);
 pinMode(trigPin,OUTPUT);
 pinMode(echoPin,INPUT);
 pinMode(6,OUTPUT);
 delay(1000);
  
  digitalWrite(trigPin,0);
  delayMicroseconds(2);
   digitalWrite(trigPin,1);
  delayMicroseconds(10);
   digitalWrite(trigPin,0);
   Duration=pulseIn(echoPin,HIGH);
   Distance=(Duration/2)/29.1;
   abc =Distance;
   Serial.println(abc);
   lcd.setCursor(0,0);
   lcd.print("Ht. Measurement");
   lcd.setCursor(0,1);
   lcd.print("Height=   ");
   lcd.setCursor(7,1);
   lcd.print(abc);
   lcd.setCursor(10,1);
   lcd.print("cm");
   delay(10000);
   
   
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(trigPin,0);
  delayMicroseconds(2);
   digitalWrite(trigPin,1);
  delayMicroseconds(10);
   digitalWrite(trigPin,0);
   Duration=pulseIn(echoPin,HIGH);
   Distance=(Duration/2)/29.1;
   Height = abc-Distance;
    lcd.setCursor(7,1);
   lcd.print("    ");
   lcd.setCursor(7,1);
   lcd.print(Height);
 
   Serial.print("Height=");
   
   Serial.println(Height);
    lcd.setCursor(11,1);
   lcd.print("cm");
   
   delay(1000);
 
}
    
