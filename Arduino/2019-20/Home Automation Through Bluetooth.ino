char d;
void setup()  // put your setup code here, to run once:
  {
     Serial.begin(9600);
     pinMode(12,OUTPUT);
  }

void loop() // put your main code here, to run repeatedly:
{
  if (Serial.available())
  {
     d=Serial.read();
    Serial.println(d);
//  if (d=='1')
//    {
//      digitalWrite(12,1);
//      Serial.print("led on");
//    }
//  else if(d=='0')
//    {
//      digitalWrite(12,0);
//      Serial.print("led off");
//    }
//  }

  }}
