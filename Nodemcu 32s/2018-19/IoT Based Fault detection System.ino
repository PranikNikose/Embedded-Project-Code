#include <WiFi.h>
#include <WiFiClient.h>  
#include <ThingSpeak.h> 
#include "ACS712.h"
#include <LiquidCrystal.h>
const char* ssid = "ankit";  
const char* password = "123456789"; 
WiFiClient client;  
unsigned long myChannelNumber = 756443;  
const char * myWriteAPIKey = "4PUF7S66ZRRXZ8VG"; 
// initialize the library with the numbers of the interface pins
const int rs = 4, en = 16, d4 = 17, d5 = 15, d6 = 2, d7 = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
////////////////////////// Variabbe to sum up all phase voltafes //////////////////
int tot_s1_rp=0;
int tot_s2_rp=0;

int r_relay = 14;
//int y_relay = 26;
int sp1_short = 25;
int sp2_short = 26;
int theft = 27;
int fault_count = 0;
//////////////// Variabel to take analog data /////////////////////
int sec1_rp=0;

int sec2_rp=0;

//int initial_current = 33;
//int last_current = 36;

int sec1 = 32 ;
int sec2 = 36;
char f1 = 0;
char f2 = 0;
char f3 = 0;
char f4 = 0;
char f5 = 0;
char s1_open = 0;
char s2_open = 0;
char s1_short = 0;
char s2_short = 0;
char s_theft = 0;
//ACS712 sensor1(ACS712_30A, initial_current);
//ACS712 sensor2(ACS712_30A, last_current);

int count = 0;
void setup() {
  Serial.begin(9600);
  
//  sensor1.calibrate();
//  sensor2.calibrate();

  // This method calibrates zero point of sensor,
  // sensor.calibrate();
  pinMode(r_relay,OUTPUT);
//  pinMode(y_relay,OUTPUT);
  pinMode(sp1_short,INPUT);
  pinMode(sp2_short,INPUT);
  pinMode(theft,INPUT);
  digitalWrite(r_relay,0);
//  digitalWrite(y_relay,0);
   lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Fault & Theft Det.");
  
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
}

void loop() {
  
    for(int i=0;i <= 60; i++)
  {
  sec1_rp = analogRead(sec1);
  
  sec2_rp = analogRead(sec2);
  
  // print out the value you read:
  tot_s1_rp = tot_s1_rp + sec1_rp;
  
  tot_s2_rp = tot_s2_rp + sec2_rp;
  delay(1);        // delay in between reads for stability
  }
  tot_s1_rp = tot_s1_rp/60;
  tot_s2_rp = tot_s2_rp/60;
//  float Ir = sensor1.getCurrentAC();
//  float Iy = sensor2.getCurrentAC();

  // To calculate the power we need voltage multiplied by current
  //float P = U * I;
Serial.print("    Section1_Voltage"); 
Serial.print(tot_s1_rp); 
Serial.print("    Section2_Voltage"); 
Serial.println(tot_s2_rp);
Serial.print("  sp1_short = ");
Serial.println(digitalRead(sp1_short));
Serial.println(digitalRead(sp2_short));
Serial.println(digitalRead(theft));
//Serial.print("  Iy = ");
//Serial.println(Iy);

//if(count == 0)
//{
//  Serial.println("Data Sending to Thingspeak field 1");
//  ThingSpeak.writeField(myChannelNumber, 1, f1, myWriteAPIKey); 
//  delay(20000);
//  Serial.println("Data Sending to Thingspeak field 2");
//  ThingSpeak.writeField(myChannelNumber, 2, f2, myWriteAPIKey);
//  delay(20000);
//  Serial.println("Data Sending to Thingspeak field 3");
//  ThingSpeak.writeField(myChannelNumber, 3, f3, myWriteAPIKey);
//  delay(20000);
//  Serial.println("Data Sending to Thingspeak field 4");
//  ThingSpeak.writeField(myChannelNumber, 4, f4, myWriteAPIKey);
//  delay(20000);
//  Serial.println("Data Sending to Thingspeak field 5");
//  ThingSpeak.writeField(myChannelNumber, 5, f5, myWriteAPIKey);
//  delay(20000);
//  count = count+1;
//}
if(tot_s1_rp > 700 && tot_s2_rp > 700 && digitalRead(sp1_short) == 0 && digitalRead(sp2_short) == 0 && digitalRead(theft) == 0)
{ 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Fault & Theft Det.");
  lcd.setCursor(0,1);
  lcd.print("No Fault       ");
  f1 = 0;
  f2 = 0;
  f3 = 0;
  f4 = 0;
  f5 = 0;
}
else
if(tot_s1_rp < 700 && tot_s2_rp < 700 && digitalRead(sp1_short) == 0 && digitalRead(sp2_short) == 0 && digitalRead(theft) == 0)
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Fault & Theft Det.");
  lcd.setCursor(0,1);
  lcd.print("Sec1 Open Ckt.  ");
  f1 = 1;
  Serial.println("Sending 1 to Thingspeak field 1");
  ThingSpeak.writeField(myChannelNumber, 1, f1, myWriteAPIKey);
  delay(20000);
  s1_open=1;
//  ThingSpeak.writeField(682546, 2, tot_s2_rp, " 9GXWK2ILHC96QD4B");
//  delay(20000); 
}
if(tot_s1_rp > 700 && tot_s2_rp < 700 && digitalRead(sp1_short) == 0 && digitalRead(sp2_short) == 0 && digitalRead(theft) == 0)
{ 
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Fault & Theft Det.");
  lcd.setCursor(0,1);
  lcd.print("Sec2 Open Ckt.   ");
  f2 = 1;
  Serial.println("Sending 1 to Thingspeak field 2");
  ThingSpeak.writeField(myChannelNumber, 2, f2, myWriteAPIKey);
  delay(20000); 
  s2_open = 1;
////  ThingSpeak.writeField(682546, 2, tot_s2_rp, " 9GXWK2ILHC96QD4B");

}
else
if(digitalRead(sp1_short) == 1 && digitalRead(sp2_short) == 0 && digitalRead(theft) == 0)
{ 
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Fault & Theft Det.");
  lcd.setCursor(0,1);
  lcd.print("Sec1 Short Ckt.   ");
  f3 = 1;
  Serial.println("Sending 1 to Thingspeak field 3");
  ThingSpeak.writeField(myChannelNumber, 3, f3, myWriteAPIKey);
   delay(20000);
   s1_short = 1;
////    ThingSpeak.writeField(682546, 1, Ir, " 9GXWK2ILHC96QD4B");
 
 }
else
if(digitalRead(sp1_short) == 0 && digitalRead(sp2_short) == 1 && digitalRead(theft) == 0)
{ 
  f4 = 1;
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Fault & Theft Det.");
  lcd.setCursor(0,1);
  lcd.print("Sec2 Short Ckt.   ");
  Serial.println("Sending 1 to Thingspeak field 4");
  ThingSpeak.writeField(myChannelNumber, 4, f4, myWriteAPIKey);
////   ThingSpeak.writeField(682546, 1, Ir, " 9GXWK2ILHC96QD4B");
  delay(20000);
  s2_short = 1;
}
else
if(digitalRead(sp1_short) == 0 && digitalRead(sp2_short) == 0 && digitalRead(theft) == 1)
{ 
 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Fault & Theft Det.");
  lcd.setCursor(0,1);
  lcd.print("Theft Detected  ");
   f5 = 1;
  Serial.println("Sending 1 to Thingspeak field 5");
  ThingSpeak.writeField(myChannelNumber, 5, f5, myWriteAPIKey); 
  delay(20000);
  s_theft = 1;
}
delay(500);
///////////////////////////////////////////////////////////////////////////////////
///////////////// Clearing Fults //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
if(tot_s1_rp > 700 &&  (s1_open==1))
  { 
    Serial.println("Sending 0 to Thingspeak field 1");
    lcd.setCursor(0,1);
    lcd.print("No Fault       ");
     ThingSpeak.writeField(myChannelNumber, 1, 0, myWriteAPIKey); 
     delay(20000);
     s1_open=0;
  }
  else if (tot_s2_rp > 700 && s2_open== 1)
  {
    Serial.println("Sending 0 to Thingspeak field 2");
    lcd.setCursor(0,1);
    lcd.print("No Fault       ");
    ThingSpeak.writeField(myChannelNumber, 2, 0, myWriteAPIKey);
    delay(20000);
    s2_open = 0;
  }
  else if(digitalRead(sp1_short) == 0 &&  (s1_short== 1))
  { 
    Serial.println("Sending 0 to Thingspeak field 3");
    lcd.setCursor(0,1);
    lcd.print("No Fault       ");
    ThingSpeak.writeField(myChannelNumber, 3, 0, myWriteAPIKey);
    delay(20000);
    s1_short = 0;
    }
    else if(digitalRead(sp2_short) == 0 && (s2_short==1))
    {
    Serial.println("Sending 0 to Thingspeak field 4");
    lcd.setCursor(0,1);
    lcd.print("No Fault       ");
    ThingSpeak.writeField(myChannelNumber, 4, 0, myWriteAPIKey);
    delay(20000);
    s2_short = 0;}
    else if(digitalRead(theft) == 0 && s_theft== 1)
    {
      Serial.println("Sending 0 to Thingspeak field 5");
    ThingSpeak.writeField(myChannelNumber, 5, 0, myWriteAPIKey);
    lcd.setCursor(0,1);
    lcd.print("No Fault       ");
    delay(20000);
    s_theft = 0;
    
    }
}
