boolean k1 = 0; 
boolean k2 = 0;
boolean k3 = 0;

int Led1 = 13;
int Led2 = 12;
int Led3 = 11;

void setup() 
{
  Serial.begin(9600);
  pinMode(Led1,OUTPUT);
  pinMode(Led2,OUTPUT);  
  pinMode(Led3,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
}
 void loop() 
{
  /// For Led1 ///
 if (digitalRead(2) == HIGH)
  {
      if(k1 == 0)
      {
         digitalWrite(Led1, HIGH);
         Serial.println("Led1 is ON");
         k1 = 1;
      }
      else
      {
        digitalWrite(Led1, LOW);
        Serial.println("Led1 is OFF");
        k1 = 0;
      }
      while(digitalRead(2) == 1);
  }
  delay(5);
  
  if (digitalRead(3) == HIGH)
  {
      if(k2 == 0)
      {
         digitalWrite(Led2, HIGH);
         Serial.println("Led2 is ON");
         k2 = 1;
      }
      else
      {
        digitalWrite(Led2, LOW);
        Serial.println("Led2 is OFF");
        k2 = 0;
      }
      while(digitalRead(3) == 1);
  }
  delay(5);

   if (digitalRead(4) == HIGH)
  {
      if(k3 == 0)
      {
         digitalWrite(Led3, HIGH);
         Serial.println("Led3 is ON");
         k3 = 1;
      }
      else
      {
        digitalWrite(Led3, LOW);
        Serial.println("Led3 is OFF");
        k3 = 0;
      }
      while(digitalRead(4) == 1);
  }
  delay(5);
}

