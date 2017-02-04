////Group 3 stationary Radar///////

#include<Servo.h>// library for servo

int pingPin=5;// set ultra sonic sensor to pin 5

// variable for distance conversion///
long duration;

int distance;

Servo servo;// name Servo servo

void setup()// runs once
{
  pinMode(pingPin, OUTPUT);// set pin 5 output
  
  Serial.begin(9600);//open serial connection
  
  servo.attach(3);// attach servo pin 3
  
}

void loop()// will repeat
{
  for(int i=15;i<=165;i++)//scans from 15 degrees to 165 degrees
  {
    servo.write(i);
    delay(100);
    distance=calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
  
  for(int i=165;i>15;i--)//scans from 165 degrees to 15 degrees
  {
    servo.write(i);
    delay(100);
    distance=calculateDistance();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}
/////////////END CODE///////////
////////////////////////////////
/////////////FUNCTIONS BEGIN////

///////////NEW FUNCTION/////////

int calculateDistance()
{
   pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    pinMode(pingPin, INPUT);
    delayMicroseconds(1);
      int  duration = pulseIn(pingPin, HIGH);
  distance=duration*0.034/2;
  return distance;
}  

