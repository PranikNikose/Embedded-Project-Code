/****************************************
 * Include Libraries
 ****************************************/
#include <LiquidCrystal.h>   //Header file
#include <WiFi.h>            //Header file
#include <PubSubClient.h>    //Header file
#include "DHT.h"           // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11      // DHT 11
#define dht_dpin 32        // Set the GPIO32 as DHT11
DHT dht(dht_dpin, DHTTYPE);

#define WIFISSID "akki"       // Put your WifiSSID here
#define PASSWORD "akki14381"  // Put your wifi password here
#define TOKEN "A1E-Vmzf1uNIopsdnuIQKSmSPrl4StxKKq"   // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "RandomName" // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
 //int pir = 35;                                          //it should be a random and unique ascii string and different from all other devices
#define pump 4    // Set the GPIO4 as RELAY

/****************************************
 * Define Constants
 ****************************************/
#define VARIABLE_LABEL "moisture"    // Assing the variable label
#define VARIABLE_LABEL1 "humidity"   // Assing the variable label
#define VARIABLE_LABEL2 "temp"       // Assing the variable label
#define VARIABLE_LABEL3 "ph"         // Assing the variable label
#define VARIABLE_LABEL_SUBSCRIBE "pump"     // Assing the variable label
#define DEVICE_LABEL "esp32" // Assig the device label

const int rs = 25, en = 26, d4 = 23, d5 = 22, d6 = 21, d7 = 19;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


char mqttBroker[]  = "things.ubidots.com";
char payload[100];

char topic[150];
char topichum[150];
char topicph[150];
char topictemp[150];

char topicSubscribe[100];
// Space to store values to send
char str_sensor[10];

/****************************************
 * Auxiliar Functions
 ****************************************/
WiFiClient ubidots;
PubSubClient client(ubidots);



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
      client.subscribe(topicSubscribe);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  
  if (message == "0") {
    digitalWrite(pump, LOW);
  } else {
    digitalWrite(pump, HIGH);
  }
  
  Serial.write(payload, length);
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT 
  pinMode(pump, OUTPUT);
  pinMode(18, OUTPUT);   //buzzer
  pinMode(35, INPUT);    //PIR
  
lcd.begin(16, 2);
lcd.print("IoT Bse Agri Sys");
delay(1000);
lcd.clear();
lcd.print("IoT Bse Agri Sys");
delay(1000);
lcd.clear();
lcd.print("IoT Bse Agri Sys");
delay(1000);
lcd.clear();
  Serial.println();
  Serial.print("Wait for WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);

    
  }
  
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);

  sprintf(topicSubscribe, "/v1.6/devices/%s/%s/lv", DEVICE_LABEL, VARIABLE_LABEL_SUBSCRIBE);
  
  client.subscribe(topicSubscribe);
}

void loop() {
  if (!client.connected()) {
    client.subscribe(topicSubscribe);   
    reconnect();
  }


/****************************************
 * Moisture
 ****************************************/
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label
  
  int moisture = analogRead(34);
  moisture=map(moisture,4095,0,0,4095);
  Serial.print("Value of Sensor is:- ");
  Serial.println(moisture);
  digitalWrite(pump, HIGH);
  if (moisture > 500)
  digitalWrite(pump, 0);
  lcd.setCursor(0, 0);
lcd.print("M=");
lcd.setCursor(2, 0);
lcd.print(moisture);
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(moisture, 4, 2, str_sensor);
  
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
  client.loop();
  delay(1000);
  /****************************************
* DHT Sensor
 ****************************************/
 //Humidity Prog
 sprintf(topichum, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL1); // Adds the variable label
  
   int h = dht.readHumidity();
   lcd.setCursor(6, 0);
lcd.print("H=");
lcd.setCursor(8, 0);
lcd.print(h);
   //float t = dht.readTemperature(); 
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(h, 4, 2, str_sensor);
  
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloudhum");
  client.publish(topichum, payload);
  client.loop();
  delay(2000);

  //Temp Prog
  sprintf(topictemp, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL2); // Adds the variable label
  
   
   int t = dht.readTemperature(); 
  Serial.println(t);
  lcd.setCursor(11, 0);
lcd.print("T=");
lcd.setCursor(13, 0);
lcd.print(t);
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(t, 4, 2, str_sensor);
  
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloudtemp");
  client.publish(topictemp, payload);
  client.loop();
  delay(2000);

  /****************************************
 * ph
 ****************************************/
  sprintf(topicph, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL3); // Adds the variable label
  
  int ph = analogRead(33);
 
  Serial.print("Value of ph is:- ");
  Serial.println(ph);
  lcd.setCursor(0, 1);
lcd.print("Ph=");
lcd.setCursor(3, 1);
lcd.print(ph);
  
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(ph, 4, 2, str_sensor);
  
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topicph, payload);
  client.loop();
  delay(1000);

  /****************************************
 * PIR Sensor
 ****************************************/
  
//  long pir = digitalRead(35);
//  delay(1000);
//    if(pir == HIGH){
//      digitalWrite (18, HIGH);
//      Serial.println("Motion detected!");
//      lcd.setCursor(7, 1);
//      lcd.print("Motion Det");
//    }
//    else {
//      digitalWrite (18, LOW);
//      Serial.println("Motion absent!");
//      lcd.setCursor(7, 1);
//      lcd.print("             ");
      }

