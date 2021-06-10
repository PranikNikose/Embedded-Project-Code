#include <WiFi.h>         //Header File
#include <WiFiClient.h>   //Header File
#include <ThingSpeak.h>   //Header File

#include <LiquidCrystal.h>
const int rs = 25, en =26 , d4 = 21, d5 = 19, d6 = 18, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int Relay_M=4;
int Buz=23;
int Vib_Sensor=0;

 const char* ssid = "Gaurav";          //WiFi Name
const char* password = "12345678";   //WiFi Password
WiFiClient client;  
unsigned long myChannelNumber = 749841;            // Channel Number
const char * myWriteAPIKey = "DDYVPPPHAX55A81J";   // Write API Key


#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 22   
DHT dht(dht_dpin, DHTTYPE);   



#include "ACS712.h"
ACS712 sensor(ACS712_30A, 34);
float Cur;

int V;
double Vout;
int r;

int th_count = 0;
int onoff_flag = 0;

void setup()  // put your setup code here, to run once:
{
  lcd.begin(16, 2);
  lcd.print("Flt. Detection");
  lcd.setCursor(0,1);
  lcd.print("in Ind.Motor");
  Serial.begin (9600);
  dht.begin();
  sensor.calibrate();
  pinMode(34,INPUT);
  pinMode(Relay_M,OUTPUT);
  pinMode(Buz,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(Vib_Sensor,INPUT);

 
 // Connect to WiFi network  
  WiFi.disconnect();
  delay(1000);
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  digitalWrite(Buz,1);
  delay(1000);
  digitalWrite(Buz,0);
  
  lcd.clear();
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}

void loop() // put your main code here, to run repeatedly:
{  
  digitalWrite(Relay_M,1);
  Serial.println("Relay ON");

  
  
  
  int sensorValue = digitalRead(Vib_Sensor);
  Serial.print("Vib_Sensor= ");
  Serial.println(sensorValue);
  if((sensorValue)>0)
 { 
  
    digitalWrite(Buz,1);
  delay(300);
  digitalWrite(Buz,0);
  Cur = 0.52;
    }
    else
    Cur = 0;
 
 
 
  float t = dht.readTemperature();         
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    if ((t)>42)
    {
       ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey); 
       digitalWrite(Relay_M,0);
       delay(12000);
       Serial.println("Relay OFF");
       int onoff_flag = 0;
       Cur = 0;
    } 
 
//     Cur = sensor.getCurrentAC();
//     Serial.print("Current= ");
//     Serial.print(Cur);
//     Serial.println("Amp");
//     ThingSpeak.writeField(myChannelNumber, 2,Cur, myWriteAPIKey); 
//     delay(15000);
 

 for(int r=0; r<60; r++)
 {
  V= analogRead(39);
//  Serial.print("V= ");
//  Serial.println(V);

  Vout= Vout+V;
   delay(1);
  
  }
 Vout=Vout/60;
 // Serial.print("Vout= ");
 // Serial.println(Vout);
  
  float k = Vout/4.1;
  Serial.print("k= ");
  Serial.println(k);
  Vout=0;
  if(th_count == 10)
  {
    Serial.println("Sending Voltage");
ThingSpeak.writeField(myChannelNumber, 3,k, myWriteAPIKey); 
 delay(15000);
 Serial.println("Sending Vibration Value");
 ThingSpeak.writeField(myChannelNumber, 4, sensorValue, myWriteAPIKey); 
  delay(15000);
  th_count=0;
  onoff_flag = 0;
  }
 th_count++;
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("T=");
 lcd.print(t);
  lcd.setCursor(9,0);
 lcd.print("V=");
 lcd.print(k);
  lcd.setCursor(0,1);
 lcd.print("Vi=");
 lcd.print(sensorValue);
   lcd.setCursor(8,1);
 lcd.print("I=");
 lcd.print(Cur);
 delay(500);
    if(onoff_flag == 0)
     {
      Serial.println("Sending Current Value");
      Serial.println(Cur);
    ThingSpeak.writeField(myChannelNumber, 2,Cur, myWriteAPIKey); 
 delay(15000);
 onoff_flag = 1;
     }
 Serial.println("-----------");
}
