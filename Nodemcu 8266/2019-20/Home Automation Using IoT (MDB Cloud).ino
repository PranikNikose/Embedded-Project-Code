#include "ESP8266WiFi.h"
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
const char *ssid =  "Realme 5 Pro";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
//int status;
//int Buzzer=D8;
String getstatus;
WiFiClient client;
int Led1= 16;   // Assigning Pin D0 as the name LED1
int Led2= 5;    // Assigning Pin D1 as the name LED2
int Relay1= 4;  // Assigning Pin D2 as the name Relay1
int Relay2= 0; 
int Switch= D8;
int Swread;
void setup() 
{
 delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, pass); 
   pinMode(15, OUTPUT); 
  pinMode(Led1, OUTPUT);     // Declaring LED1 pin as an output.
pinMode(Led2, OUTPUT);     // Declaring LED2 pin as an output.
pinMode(Relay1, OUTPUT);   // Declaring Relay1 pin as an output.
pinMode(Relay2, OUTPUT);   // Declaring Relay2 pin as an output.
pinMode(D7, OUTPUT);
pinMode(Switch, INPUT);
pinMode(LED_BUILTIN, OUTPUT);
if(WiFi.status() != WL_CONNECTED)
   {
    Serial.print(".");
   }
    else
    { 
      Serial.println(" ");
      Serial.println("Connected");
      digitalWrite(15,HIGH);
      delay(1000);
    }
}

void loop() {
String Link;
HTTPClient http;
//----------------------------------------------//------------------------------------//
  Link="http://mdbelectrosoft.in/MDBES/Workshop.php?unit=50";
  
    http.begin(Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  //Serial.println(httpCode1);   //Print HTTP return code
   
  //Serial.println(payload);    //Print request response payload
  int myvalue=payload.toInt();
  if (myvalue == 0) 
   {
      digitalWrite(Led1,LOW);     // Making LED1 LOW.
      Serial.println("Led1 off");
   }
  else if (myvalue == 1) 
     {
      digitalWrite(Led1,HIGH);    // Making LED1 HIGH.
      Serial.println("Led1 on");
     }
  else if (myvalue == 2) 
     {
      digitalWrite(Led2,LOW);     // Making LED2 LOW.
      Serial.println("led2 off");
     }
  else if (myvalue == 3) 
     {
      digitalWrite(Led2,HIGH);    // Making LED2 HIGH.
      Serial.println("Led2 on");
     }
  else if (myvalue == 4) 
     {
      digitalWrite(Relay1,LOW);   // Making Relay1 LOW.
      Serial.println("Relay1 off");
     }
  else if (myvalue == 5) 
     {
      digitalWrite(Relay1,HIGH);  // Making Relay1 HIGH.
      Serial.println("Relay1 on");
     }
  else if (myvalue == 6) 
     {
      digitalWrite(Relay2,LOW);   // Making Relay2 LOW.
      Serial.println("Relay2 off");
     }
  else if (myvalue == 7)
     {
      digitalWrite(Relay2,HIGH);  // Making Relay2 HIGH.
      Serial.println("Relay2 on");
     }
  else if (myvalue == 8)
     {
      digitalWrite(Led1,LOW);    // Making Led1 LOW.
      digitalWrite(Led2,LOW);    // Making Led2 LOW.
      digitalWrite(Relay1,LOW);  // Making Relay1 LOW.
      digitalWrite(Relay2,LOW);  // Making Relay2 LOW.
      Serial.println("All Off");
     }
  else  if (myvalue == 9)
     {
      digitalWrite(Led1,HIGH);    // Making Led1 HIGH.
      digitalWrite(Led2,HIGH);    // Making Led2 HIGH.
      digitalWrite(Relay1,HIGH);  // Making Relay1 HIGH.
      digitalWrite(Relay2,HIGH);  // Making Relay2 HIGH.
      Serial.println("All On");
     }
     Swread=digitalRead(Switch);
     Serial.print("SwRead=");
Serial.println(Swread);
 
  http.end();  //Close connection

  //delay(5000);
}
