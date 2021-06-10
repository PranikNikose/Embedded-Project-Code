#include <WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 18, 19, 21, 22, 23);

#include "DHT.h"        
#define DHTTYPE DHT11
#define dht_dpin 0   
DHT dht(dht_dpin, DHTTYPE); 

#define trigPin 4
#define echoPin 16
int count =0;
int hbs=35;
int count2=0;
int buz=17;
int s = 0;
int b = 0;
int tmp = 0;
long Duration,Distance;  

const char* ssid = "nsk";
const char* password = "nakul4727";
WiFiClient client;
unsigned long myChannelNumber = 747710;
const char * myWriteAPIKey = "8N43U5YC4PGWBLQB";

void setup() {
dht.begin();
Serial.println("Humidity and temperature\n\n");
delay(700); 
Serial.begin(9600);
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

  // Print the IP address
Serial.println(WiFi.localIP());
ThingSpeak.begin(client);
delay(1000);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(buz,OUTPUT);
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("    Patient ");
lcd.setCursor(0,1);
lcd.print("   Monitoring ");


s = 0;
ThingSpeak.writeField(myChannelNumber, 1, s, myWriteAPIKey);
delay(20000);

tmp = 0;
ThingSpeak.writeField(myChannelNumber, 2, tmp, myWriteAPIKey);
delay(20000);

b = 0;
ThingSpeak.writeField(myChannelNumber, 3, b, myWriteAPIKey);
delay(20000);

}

void loop() {
digitalWrite(trigPin,0);
delayMicroseconds(2);
digitalWrite(trigPin,1);
delayMicroseconds(10);
digitalWrite(trigPin,0);
Duration=pulseIn(echoPin,HIGH);
Distance=(Duration/2)/29.1;
Serial.print("Distance=");
Serial.println(Distance);
delay(100);
if(Distance>=5 && count==0)
{
lcd.setCursor(0, 0);
lcd.print("Saline is 50%");
Serial.println("sending data1");
lcd.setCursor(0, 1);
lcd.print("                        ");

s = Distance;
ThingSpeak.writeField(myChannelNumber, 1, s, myWriteAPIKey);
delay(20000);
count=1;
}
    
if(Distance>10 && count==1)
{
lcd.setCursor(0, 0);
lcd.print("Plz check saline");
Serial.println("sending data2");
s = Distance;
ThingSpeak.writeField(myChannelNumber, 1, s, myWriteAPIKey);
delay(20000);;
count=3;
    //delay(2000);
digitalWrite(buz,1);
}
     
     
float h = dht.readHumidity();
float t = dht.readTemperature();         
Serial.print("Current humidity = ");
Serial.print(h);
Serial.print("%  ");
Serial.print("temperature = ");
Serial.print(t); 
Serial.println("C  ");
delay(800);
lcd.setCursor(0,1);
lcd.print("T:       ");
lcd.setCursor(2,1);
lcd.print(t);
if(t>38)
{
tmp = t;
ThingSpeak.writeField(myChannelNumber, 2, tmp, myWriteAPIKey);
delay(20000);
}
  

 //heart beat sensor
double k = millis();
while ((millis() - k) <= 5000)
{
if (analogRead(hbs) < 100)
   {
   count2 = count2 + 1;
   delay(300);
   while(analogRead(hbs)< 100);
 }
}
int beat = count2 * 12;
Serial.print("beats=");
Serial.println(beat);
Serial.println("  ");
delay(500);

lcd.setCursor( 9,1);
lcd.print("BPM:     ");
lcd.setCursor(13,1);
lcd.print(beat);

if(beat>100)
{
b= beat;
ThingSpeak.writeField(myChannelNumber, 3, b, myWriteAPIKey);
delay(20000);
}
count2=0;

}
