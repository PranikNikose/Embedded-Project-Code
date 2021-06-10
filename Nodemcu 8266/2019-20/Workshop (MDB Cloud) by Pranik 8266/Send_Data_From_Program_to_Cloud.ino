#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
const char *ssid =  "MDB";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
 String getstatus;
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  WiFi.begin(ssid, pass); 
}

void loop() {
  // put your main code here, to run repeatedly:
String Link;
HTTPClient http;

   if(WiFi.status() != WL_CONNECTED)
   { Serial.print(".");
    
    //status=0;    
    }
    else
    { 
      Serial.println(" ");
      Serial.print("Connected");

      Link="http://mdbelectrosoft.in/MDBES/Workshop.php?unit=49&sensor=2929";

    http.begin(Link);     //Specify request destination
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  //Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println("first Data Send Succesfully to Field49 = ");
}
}
