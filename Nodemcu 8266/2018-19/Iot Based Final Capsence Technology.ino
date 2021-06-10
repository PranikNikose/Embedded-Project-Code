
#include <WiFi.h>  // Header file 
#include <WiFiClient.h>   // Header file
#include <ThingSpeak.h>   // Header file

boolean k1 = 0;
boolean k2 = 0;
boolean k3 = 0;
  
boolean Change = 0;


int Relay1=21;
int Relay2=19;
int Relay3=18;
int Buz= 4;

# define S1 25    /// Touch Sensor(S3) is attached to GPIO 25
# define S2 26    /// Touch Sensor(S4) is attached to GPIO 26
# define S3 27    /// Touch Sensor(S5) is attached to GPIO 27

int  i;         // Assigning i  
 
WiFiClient client;   // Creates a client that can connect to to a specified internet IP address

void setup()         // Code under this setup run once.
{
//i = 0;

Serial.begin(9600);        // Sets the data rate in bits per second (baud) for serial data transmission
ThingSpeak.begin(client); 
   
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT); 
  pinMode(Buz,OUTPUT);  
  
  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  pinMode(S3,INPUT);
  
  pinMode(36,INPUT);
  
  WiFi.disconnect();
  delay(100);
   WiFi.begin("Pranik Nikose","Pranik@123");              //("Wifi Name","Wifi Password")
  while ((!(WiFi.status() == WL_CONNECTED)))
   { 
    delay(300);
    Serial.print(".");
   }
   Serial.println("");
  Serial.println("Connected to WiFi");
      
  digitalWrite(Buz,1);
  delay(500);
  digitalWrite(Buz,0);     
  
}


void loop()           // Code under this loop runs forever.
{
  if (digitalRead(36)==HIGH)
  {
    if(Change==0)
    {
    Serial.println("IOT based Home Automation");
    Change=1;
    }
   i= ThingSpeak.readIntField(560931,1,"ZNAEDRX46QWI9DSG");     //(myChannelNumber,fieldnumber,myReadAPIKey)
   
    
   if (i == 11) 
     {
      digitalWrite(Relay1,LOW);   // Making Relay1 LOW.
      Serial.println("Relay1 OFF");
     }
  else if (i == 12) 
     {
      digitalWrite(Relay1,HIGH);  // Making Relay1 HIGH.
      Serial.println("Relay1 ON");
     }
  else if (i == 13) 
     {
      digitalWrite(Relay2,LOW);   // Making Relay2 LOW.
      Serial.println("Relay2 OFF");
     }
  else if (i == 14)
     {
      digitalWrite(Relay2,HIGH);  // Making Relay2 HIGH.
      Serial.println("Relay2 ON");
     }
     else if (i == 15) 
     {
      digitalWrite(Relay3,LOW);   // Making Relay2 LOW.
      Serial.println("Relay3 OFF");
     }
  else if (i == 16)
     {
      digitalWrite(Relay3,HIGH);  // Making Relay2 HIGH.
      Serial.println("Relay3 ON");
     }
     
  else if (i == 17)
     {
      
      digitalWrite(Relay1,LOW);  // Making Relay1 LOW.
      digitalWrite(Relay2,LOW);  // Making Relay2 LOW.
      digitalWrite(Relay3,LOW); 
      Serial.println("All OFF");
     }
  else if (i == 18)
     {
      digitalWrite(Relay1,HIGH);  // Making Relay1 HIGH.
      digitalWrite(Relay2,HIGH);  // Making Relay2 HIGH.
      digitalWrite(Relay3,HIGH);  // Making Relay2 HIGH.
      Serial.println("All ON");
     }
  
  }
  else
  {
    if(Change==1)
    {
    Serial.println("Capsence Technology");
    Change=0;
    }

       /// For Relay1 ///
   if (digitalRead(S1) == HIGH)
  {
      if(k1 == 0)
      {
         digitalWrite(Relay1, HIGH);
         Serial.println("Relay1 is ON");
         k1 = 1;
      }
      else
      {
        digitalWrite(Relay1, LOW);
        Serial.println("Relay1 is OFF");
        k1 = 0;
      }
      while(digitalRead(S1) == 1);
  }
 

  /// For Relay2 ///
 if (digitalRead(S2) == HIGH)
  {
      if(k2 == 0)
      {
         digitalWrite(Relay2, HIGH);
         Serial.println("Relay2 is ON");
         k2 = 1;
      }
      else
      {
        digitalWrite(Relay2, LOW);
        Serial.println("Relay2 is OFF");
        k2 = 0;
      }
      while(digitalRead(S2) == 1);
  }


  
  /// For Relay3 ///
 if (digitalRead(S3) == HIGH)
  {
      if(k3 == 0)
      {
         digitalWrite(Relay3, HIGH);
         Serial.println("Relay3 is ON");
         k3 = 1;
      }
      else
      {
        digitalWrite(Relay3, LOW);
        Serial.println("Relay3 is OFF");
        k3 = 0;
      }
      while(digitalRead(S3) == 1);
  }
 
    
  }
}
