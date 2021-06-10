//const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


////// I2C Display :  SDA = 4(D2)   & SCL = 5(D1)   /////////////////////////
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


#include "DHT.h"          // including the library of DHT11 temperature and humidity sensor

#include <ESP8266WiFi.h>  // Header File
#include <WiFiClient.h>   // Header File
#include <ThingSpeak.h>   // Header File

int pH_sensor= D7;   // pH_sensor input at digital PIN 13 (D7)
int pHvalue= 0;      // Variable To store the ph value

int sense_Pin= A0;    // Soil Moisture Sensor input at Analog pin A0
int value= 0;        // Variable To store the moisture value

int relay=D6;           // Relay Connected 12 (D6)

#define dht_dpin 15        //DHT11 is connected to 15 (D8)
#define DHTTYPE DHT11      // dht type
 int  i ;                  // variable
 int Buzzer = D0 ;           // Buzzer is connected to 16 (D0)
 
DHT dht(dht_dpin, DHTTYPE); //declaring Dht pin and Dht type//

const char* ssid = "--------";           // WiFi Name
const char* password = "--------";   // WiFi Password

WiFiClient client;  
unsigned long myChannelNumber = 560931 ;           // Channel Number
const char * myWriteAPIKey = "C5JMFKL9U8VRNU7S";  // Write API Key in side "----"

void setup()       // Code under this setup run once.
{
  Serial.begin(9600);    // Set Baud rate to 9600
  
  lcd.init();         //intialization for lcd       
  lcd.init();         //intialization for lcd   
  lcd.backlight();    //backlight on for lcd   

  lcd.setCursor(0,0);   //C,R
  lcd.print("Project Name");
  delay(500);
  
  dht.begin();
  Serial.println("Humidity and temperature\n\n");

   pinMode(Buzzer, OUTPUT);   // Declaring Buzzer pin as an output.
   pinMode(pH_sensor,INPUT);  // Declaring pH_sensor pin as an INPUT.
   pinMode(sense_Pin,INPUT);  // Declaring sense_Pin pin as an INPUT.
   pinMode(relay, OUTPUT);    // Declaring relay pin as an output.
  
   
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
  Serial.println("WiFi connected");    
  
   // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);   
}

void loop()          // Code under this loop runs forever. 
{
  lcd.clear();
  //////////moisture//////////
  
   Serial.print("MOISTURE LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);
   if(value<50)  /// value maybe 50 or 500 depends upon fraction and bit//
   {
      digitalWrite(relay, 1);   // Making relay HIGH.
   }
   else
   {
      digitalWrite(relay,0);    // Making relay LOW.
   }
   delay(100);
   digitalWrite(relay,LOW);       // Making relay LOW.


   ///////DHT////////////////
   
    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    
    if (t>38)
    {digitalWrite(Buzzer,1);}
   else 
   {digitalWrite(Buzzer,0);}
  

/////pH//////////////
   Serial.print("pH Value : ");
   pHvalue= digitalRead(pH_sensor);
   pHvalue= value/10;
   Serial.println(pHvalue);

   lcd.setCursor(0, 0);  //CR
   lcd.print("Moistr:"); //lcd.setCursor(6, 0);  //CR
   lcd.print(value);     //lcd.setCursor(10, 0);
   lcd.print("T:");      // lcd.setCursor(12, 0);
   lcd.print(t);         // lcd.setCursor(14, 0);
   lcd.print("°C");

   lcd.setCursor(0, 1);
   lcd.print("hum:");     //lcd.setCursor(4, 1);
   lcd.print(h);          //lcd.setCursor(6, 1);
   lcd.print("%");        //lcd.setCursor(8, 1);
   lcd.print("pH:");      //lcd.setCursor(11, 1);
   lcd.print(pHvalue);

   ///Tempertaure on Thingspeak////
      ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey); 
      delay(15000);                  // ThingSpeak will only accept updates every 15 seconds.

   ///Humidity on Thingspeak////
       ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey); 
      delay(15000);  

   ///Moisture on Thingspeak////
      ThingSpeak.writeField(myChannelNumber, 3, value, myWriteAPIKey); 
      delay(15000);                  // ThingSpeak will only accept updates every 15 seconds.

   ///pH value on Thingspeak////
       ThingSpeak.writeField(myChannelNumber, 4, pHvalue, myWriteAPIKey); 
      delay(15000);    

      
   
}
