int IN1=7;
int IN2=6;

char t;
void setup() 
{
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);

Serial.begin(9600);
}

void loop() 
{
digitalWrite(13,0);
if(Serial.available())
{
  t = Serial.read();
  Serial.println(t);
}
if(t == 'f')
{
  //move forward
  Serial.println("Forward");
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
//digitalWrite(IN3,HIGH);
//digitalWrite(IN4,LOW);
}
else if(t == 'b')
{ 
  //move reverse
  Serial.println("Backward");
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
//digitalWrite(IN3,LOW);
//digitalWrite(IN4,HIGH);
}
else if(t == 's')
{ 
  //turn left
  Serial.println("Stop");
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
//digitalWrite(IN3,HIGH);
//digitalWrite(IN4,LOW);
}
}
