#include <WiFi.h>  //Header File
#include <WiFiClient.h>   //Header File
#include <ThingSpeak.h>   //Header File
#include <HTTPClient.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 25, en = 26, d4 = 27, d5 = 22, d6 = 21, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int f1 = 0, f2 = 0;   //flags 
int Relay_M=19;
int Relay_D1=5;
int Relay_D2=18;
int th_count = 0;
int status;
String Link;
HTTPClient http;
String getstatus;

 const char* ssid = "akki";          //WiFi Name
const char* password = "akki14381";   //WiFi Password
WiFiClient client;  
unsigned long myChannelNumber = 748710;            // Channel Number
const char * myWriteAPIKey = "Z46IJ5I10PWFFHUJ";   // Write API Key


#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 23   
DHT dht(dht_dpin, DHTTYPE);   

int Count=0;
double st=0;
int Speed;
int Hall_Sensor=36;
int onoff_flag = 0;
#include "ACS712.h"
ACS712 sensor(ACS712_30A, 32);
float Cur;

int V;
double Vout;
int r;

void setup()  // put your setup code here, to run once:
{
  Serial.begin (9600);
  dht.begin();
  pinMode(Hall_Sensor,INPUT);
  sensor.calibrate();
  pinMode(39,INPUT);
  pinMode(Relay_M,OUTPUT);
  pinMode(Relay_D1,OUTPUT);
  pinMode(Relay_D2,OUTPUT);
  
  digitalWrite(Relay_M,1);   //motor stop
  digitalWrite(Relay_D1,0);
  digitalWrite(Relay_D2,0);
 
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
  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client); 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Indn Motor Para");
  delay(1000);
  lcd.clear(); 
}

void loop() // put your main code here, to run repeatedly:
{
  //lcd.begin(16,2);
    Link= "https://mahavidyalay.in/AcademicDevelopment/ServerDemo/ShowLed5.php";
    http.begin(Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  if((payload)=="1")
    {
    Serial.println("ON");
    digitalWrite(Relay_M,0);    ///Mains ON
    Cur=2.061;
     lcd.setCursor(10,1);
     lcd.print("I=");
     lcd.print(Cur);
     if(onoff_flag == 1)
     {
    ThingSpeak.writeField(myChannelNumber, 3,Cur, myWriteAPIKey); 
 delay(15000);
 onoff_flag = 0;
     }
    }
    else if ((payload)=="2")
      {
        Serial.println("OFF");
        digitalWrite(Relay_M,1);    ///Mains OFF
             
      lcd.print("      ");
      Cur = 0;
      if(onoff_flag == 0)
      {
        ThingSpeak.writeField(myChannelNumber, 3,0, myWriteAPIKey); 
        delay(15000);
        onoff_flag = 1;
      }
      }
     else if ((payload)=="3")
      {
        Serial.println("Forward");
      
      if((f1)==0)
      {
        Serial.println("Wait For 4 Seconds");
        digitalWrite(Relay_M,1);    ///Mains OFF
        delay(4000);
      }
      {
        digitalWrite(Relay_D1,1);   //Change motor direction   shiftion of relay 
      digitalWrite(Relay_D2,1);
      delay(1000);
      digitalWrite(Relay_M,0);   /// Start Motor ///Mains ON}
      f1=1;
      f2=0;
      }
      }
     else if ((payload)=="4")
      {
      Serial.println("Reverse");
      if ((f2)==0)
       { 
        Serial.println("Wait For 4 Seconds");
        digitalWrite(Relay_M,1);  ///Mains STop
        delay(4000);
        }
      {
      digitalWrite(Relay_D1,0);   ///shifting of relay for Reverse
      digitalWrite(Relay_D2,0); 
      delay(1000);
      digitalWrite(Relay_M,0);    ///Mains ON
      f2=1;
      f1=0;
      }  
      

}


  
  float t = dht.readTemperature();         
    Serial.print("temperature = ");
    lcd.setCursor(0,0);
    lcd.print("T = ");
    lcd.print(t);
    Serial.print(t); 
    Serial.println("C  ");
    if ((t)>35)
    {
       digitalWrite(Relay_M,1);    ///Mains OFF
       ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey); 
       delay(12000);
    }

    st= millis();
    while((millis()-st)<5000)
 { 
//    Serial.print("Hall_Sensor= ");
//    Serial.println(digitalRead(Hall_Sensor));
  
       if (digitalRead(Hall_Sensor)==0)
         {
           Count++;
           while(digitalRead(Hall_Sensor)==0);
         }
 }
  
 Speed = Count * 12;
 Serial.print("Speed= ");
 lcd.setCursor(10,0);
 lcd.print("s=");
 lcd.print(Speed);
 Serial.print(Speed);
 Serial.println("RPM");
 Count=0;
  
 
 
 // Cur = sensor.getCurrentAC();
//  Serial.print("Current= ");
//  Serial.print(Cur);
//  Serial.println("Amp");
 

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
  
  float k = Vout/5.3;
 // Serial.print("k= ");

 // Serial.println(k);
 lcd.begin(16,2);
  lcd.setCursor(0,0);
    lcd.print("T = ");
    lcd.print(t);
     lcd.setCursor(10,0);
 lcd.print("s=");
 lcd.print(Speed);
   lcd.setCursor(0,1);
 lcd.print("v = ");
 lcd.print(k);
 lcd.setCursor(10,1);
     lcd.print("I=");
     lcd.print(Cur);
  Vout=0;
  if(th_count == 10)
  {
ThingSpeak.writeField(myChannelNumber, 4,k, myWriteAPIKey); 
 delay(15000);
 ThingSpeak.writeField(myChannelNumber, 2, Speed, myWriteAPIKey); 
  delay(15000);
  th_count=0;
  }
 th_count++;
 Serial.println("-----------");
}
