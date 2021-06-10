int upsensor= A1;
int downsensor= A0;
int leftsensor= A3;
int rightsensor= A2;

int IN1=8;
int IN2=9;
int IN3=10;
int IN4=11;

void setup() 
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
}

void loop() 
{
 int us = analogRead(A1);
 int ds = analogRead(A0);
 int ls = analogRead(A3);
 int rs = analogRead(A2);

Serial.print("rs = ");
Serial.print(rs);
Serial.print("   ls = ");
Serial.println(ls);
 Serial.print(us-ds);
 Serial.print("////"); 
 Serial.println(rs-ls);
 
  if((us-ds)>700)
  {
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW); 
   delay(20);
   digitalWrite(IN1,0);
   
  }
  else if ((us-ds)<200)
  {
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   delay(20);
   digitalWrite(IN2,0);
  }
  else if((rs-ls)>750)
  {
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   delay(20);
   digitalWrite(IN3,0); 
  }
  else if ((rs-ls)<400)
  {
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   delay(20);
   digitalWrite(IN4,0);
  }
  delay(1000);

}
