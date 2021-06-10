#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
const char *ssid =  "MDB";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";

String getstatus;
WiFiClient client;
void setup() 
{
 delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, pass); 
if(WiFi.status() != WL_CONNECTED)
   {
    Serial.print(".");
   }
    else
    { 
      Serial.println(" ");
      Serial.println("Connected");
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
  Serial.println(myvalue);
 
  http.end();  //Close connection

  //delay(5000);
}
