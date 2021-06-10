int pump = 3;
int m11=5;
int m12=4;
int m21=7;
int m22=6;
int buz=8;
int gas=A0;
int smoke=A1;
int temp=A5;
char t;


void setup() {
  pinMode(m12,OUTPUT);
  pinMode(m11,OUTPUT);
  pinMode(m22,OUTPUT);
  pinMode(m22,OUTPUT);
  pinMode(buz,OUTPUT);
  pinMode(pump,OUTPUT);
 Serial.begin(9600);
 
  // put your setup code here, to run once:

}

void loop() {
  int sensorValue = analogRead(A5);
  float temp1=sensorValue*(5.0/1023.0);
  int Temp = temp1*100-2;
  Serial.print("Temperature=");
  Serial.println(Temp);
  delay(500);
  
  Serial.print("Smoke=");
  Serial.println(analogRead(A1));
  
  if (analogRead(temp)>130&&analogRead(A0)>400)
  {Serial.println(analogRead(temp));
  digitalWrite(3,1);
  Serial.println("Relay ON");
  digitalWrite(8,1);
  }
  else
  {
  digitalWrite(3,0);
  digitalWrite(8,0);
  }

  Serial.print("Gas=");
  Serial.println(analogRead(gas));
  delay(500);
  Serial.println("");
  if (analogRead(gas)>500)
  digitalWrite(buz,1);
  else
  digitalWrite(buz,0);  
    

if(Serial.available())
t = Serial.read();
if(t == 'f')
{ //move forward
digitalWrite(m11,HIGH);
digitalWrite(m12,LOW);
digitalWrite(m21,HIGH);
digitalWrite(m22,LOW);
}
else if(t == 'b')
{ //move reverse
digitalWrite(m11,LOW);
digitalWrite(m12,HIGH);
digitalWrite(m21,LOW);
digitalWrite(m22,HIGH);
}
else if(t == 'l')
{ //turn left

digitalWrite(m11,HIGH);
digitalWrite(m12,LOW);
digitalWrite(m21,LOW);
digitalWrite(m22,1);
t='s';
}
else if(t == 'r')
{ //turn Right

digitalWrite(m11,LOW);
digitalWrite(m12,1);
digitalWrite(m21,HIGH);
digitalWrite(m22,LOW);
delay(500);
t='s';
}
else if(t == 's')
{ //STOP
digitalWrite(m11,LOW);
digitalWrite(m12,LOW);
digitalWrite(m21,LOW);
digitalWrite(m22,LOW);
}
}
