#include <ESP8266WiFi.h>  // Header File
#include <WiFiClient.h>   // Header File
#include <ThingSpeak.h>   // Header File

const char* ssid = "hotspot";           // WiFi Name
const char* password = "12345678";   // WiFi Password
WiFiClient client;  
unsigned long myChannelNumber = 897946;           // Channel Number
const char * myWriteAPIKey = "UVKGVF2JTPO3ZNXX";  // Write API Key


int sense_Pin= A0;   // Heart Sensor input at Analog PIN A0
int value= 0;

int Buz=D3;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() 
{ 
   Serial.begin(9600);    // Set Baud rate to 9600
   delay(500);
   // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);         // Some Delay
   Serial.print(".");  
  }  
  Serial.println("");  
  delay(100);
  Serial.println("WiFi connected");    
  delay(100);
  
   // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);
     
   delay(100); 
   pinMode(D0,OUTPUT); 
   pinMode(A0,INPUT);
   pinMode(Buz,OUTPUT);

  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  digitalWrite(Buz,1);
}

void loop() 
{
  
   value=analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);
     delay(500);

   ThingSpeak.writeField(myChannelNumber, 1, value, myWriteAPIKey); 
  delay(15000);                  // ThingSpeak will only accept updates every 15 seconds. 
    
if (value>=85)
   {digitalWrite(Buz,0);}
else if(value<=85)
   {digitalWrite(Buz,1);}
   
  lcd.setCursor(0,0);   //C,R
  lcd.print("Heart Rate Alert");

  lcd.setCursor(0,1);
  lcd.print("Heartbeat=");
  lcd.print(value);
  lcd.print(" BPM");  

}
