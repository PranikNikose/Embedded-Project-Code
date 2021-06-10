#include <Servo.h>

Servo myservo1;  
Servo myservo2;  
Servo myservo3;  
 
int led = 13;                // the pin that the LED is atteched to.
int Buz=7;
int sensor = 2;              // the pin that the sensor is atteched to.
int state = LOW;             // by default, no motion detected.
int val = 0;                 // variable to store the sensor status (value).
int k;
int pos1 = 0;    // variable to store the servo position

void setup() 
{
   myservo1.attach(3);  // attaches the servo on pin 9 to the servo object
   myservo2.attach(5);
    myservo3.attach(6);
  pinMode(Buz, OUTPUT);      // initalize LED as an output.
   pinMode(led, OUTPUT); 
  pinMode(sensor, INPUT);    // initialize sensor as an input.
  Serial.begin(9600);        // initialize serial.
}

void loop()
{
  val = digitalRead(sensor);   // read sensor value.
  if (val == HIGH) 
  {           // check if the sensor is HIGH.
    
   // delay(1000);                // delay 1 second. 
    if (state == LOW) 
    {
            Serial.println("Motion detected!"); 
            digitalWrite(led, HIGH );   // turn LED ON.
              // turn LED ON.
            Serial.print("Buz");
            digitalWrite(Buz,1 ); 
            delay(100);
            digitalWrite(Buz, 0 );   // turn LED ON.


      for(k=0;k<6;k++)
      {
        for (pos1 = 0; pos1 <= 180; pos1 += 1)
 { 
    myservo1.write(pos1); 
    myservo2.write(pos1); 
    myservo3.write(pos1); 
    delay(15);                       
  }
  for (pos1 = 180; pos1 >= 0; pos1 -= 1) 
  { // goes from 180 degrees to 0 degrees
    myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos1); 
    myservo3.write(pos1); 
    delay(15);                       // waits 15ms for the servo to reach the position
  }
        
        }
      state = HIGH;       // update variable state to HIGH.
    }
  } 
  else 
   {
      //delay(1000);             // delay 2 second. 
      if (state == HIGH)
      {
//         myservo1.write(0);              // tell servo to go to position in variable 'pos'
//         myservo2.write(0); 
//         myservo3.write(0); 
        Serial.println("Motion stopped!");
              digitalWrite(led, LOW); // turn LED OFF.

        state = LOW;       // update variable state to LOW
      }
  }
}
