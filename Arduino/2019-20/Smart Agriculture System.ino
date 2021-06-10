#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 10    
DHT dht(dht_dpin, DHTTYPE); 

int sense_Pin= A2;   // Soil Sensor input at Analog PIN A0
int value= 0;

int Relay=A0;

#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  
 dht.begin();
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(A2,INPUT);
  lcd.begin(16, 2);
  //lcd.setCursor(0, 0);
  //lcd.print("Smart Agri. Sys.");
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
    int h = dht.readHumidity();
    int t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");


    Serial.print("MOISTURE LEVEL : ");
   value=analogRead(sense_Pin);
   value= value/10.33;
   Serial.println(value);

   if (value>50)
   {
    
    digitalWrite(Relay,0);
     lcd.setCursor(0, 0);
  lcd.print("Smart Agri. Sys.");
    lcd.setCursor(0, 1);
   lcd.print("T=");
   lcd.setCursor(2, 1);
   lcd.print(t);

   lcd.setCursor(5, 1);
   lcd.print("H=");
   lcd.setCursor(7, 1);
   lcd.print(h);

   lcd.setCursor(10, 1);
   lcd.print("M=");
   lcd.setCursor(12, 1);
   lcd.print(value);
   }
   else
   {
    digitalWrite(Relay,1);
     lcd.setCursor(0, 0);
  lcd.print("Smart Agri. Sys.");
    lcd.setCursor(0, 1);
   lcd.print("T=");
   lcd.setCursor(2, 1);
   lcd.print(t);

   lcd.setCursor(5, 1);
   lcd.print("H=");
   lcd.setCursor(7, 1);
   lcd.print(h);

   lcd.setCursor(10, 1);
   lcd.print("M=");
   lcd.setCursor(12, 1);
   lcd.print(value);
   }

  
}
