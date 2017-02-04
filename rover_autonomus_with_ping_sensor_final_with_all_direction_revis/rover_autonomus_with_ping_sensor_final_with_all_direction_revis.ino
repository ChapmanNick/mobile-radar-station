//group 3 rover code using ultrasonic sensor for autonomous function//
//////////////////////////////////////////////////////////////////////
#include <Servo.h> // library needed for servo commands

int E1 = 6; //M1 Speed Control 
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control

const int pingPin = 3; //ultrasonic sensor

// establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
  
long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
                                             }

Servo myservopan; //setting up servo control

void setup() 

{
  
Serial.begin(9600);//opens serial for communication mainly for testing code functionality

myservopan.attach(9);// attaches the servo on pin 9
delay(1);

myservopan.write(90);// set servo to mid-point ultrasonic facing fwd 
delay(500);


void loop() //these functions will repeat
{ 

 motorStop();// stops all motors see function below
 delay(50);
 
 float centerDis;// set variable for forward distance
 
 centerDis= pingC();// gathers sensor input attachs to center distance see function pingC
 delay(50);
 

   if (centerDis > 6) //safe forward route set to min 6 inches,
  
      {
        forward();// if distance greater than 6 inches moves forward for 4 seconds see function below
        delay(1000);
    
        motorStop();// stops motors 
        delay(50);
    
        loop();// returns to main loop function
      }
        
        else if(centerDis < 6)
               
               {
                  float distA;// set variable for route A
 
                  distA=pingAroute();//gathers input from sensor to attch to route A see below function
                  delay(50);
 
                  float distB;// set variable for route B
 
                  distB=pingBroute();// gathers input from sensor to attach route B see below function
                  delay(50);
                    
     //compare routes based on their pinged distances and choose longest clear available route.
       
               if (distA > 6 && distA > distB )// if distance A is greater performs actions in if statement.
     
                  {
                     turnA();// turns to route A.
                     delay(50);
       
                     loop();// returns to main loop.
                  }
     
                  else if(distA < distB && distB > 6)// if distance B greater performs actions in if statement                          
   
                         {
      
                           turnB();//turns to B route.
                           delay(50);
    
                           loop();//Returns to main loop
                         }
 
    
                         else if(distA && distB && centerDis < 6)//else if all three directions are less than 6 inches will perform following if statement
      
                                {
       
                                  reverse();// reverse for 2 seconds
                                  delay(50);
    
                                  turnA();//Turns to A route.
                                  delay(50);
    
                                  loop();//Returns to main loop.                  
                                }
               }
}////////////////////////END of Main Code////////////////////////////////

////////////////////////FUNCTIONS LISTED BELOW///////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//..................................new function.......................//
int motorStop()
{
  
analogWrite (E1,0);
digitalWrite(M1,LOW);
analogWrite (E2,0);
digitalWrite(M2,LOW);
Serial.print("STOP");
Serial.println("");
delay(100); 
}


//..................................new function.......................//

int pingC()// ping center
  {
    myservopan.write(90);  // set servo to mid-point ultrasonic facing fwd 
    delay(1000);
    pinMode(pingPin, OUTPUT); //perform ping function
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    pinMode(pingPin, INPUT);
    delayMicroseconds(1);
     int  distance = pulseIn(pingPin, HIGH); //represents a distance measured in time
     int  distanceInches = microsecondsToInches(distance);// convert the time into a distance
        Serial.print(distanceInches);// displays distance in inches
        Serial.print("IN. Center Distance,");
        Serial.println();
return distanceInches;
   delay(1);
  }

//..................................new function.......................//

int forward()//fwd motion
  { 
    analogWrite (E1,255);
    digitalWrite(M1,HIGH);
    analogWrite (E2,255);
    digitalWrite(M2,HIGH);
    Serial.print("FWD");
    Serial.println("");
    delay(4000);
  }

//..................................new function.......................//

int pingAroute()// ping A route
 {
    
    myservopan.write(0);  // pans servo toward route A
    
    delay(1000);// delay to allow to complete pan
   
   pinMode(pingPin, OUTPUT);// ping sensor
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(5);
   digitalWrite(pingPin, LOW);
   pinMode(pingPin, INPUT);
   delayMicroseconds(1);
     int  aroutecheck = pulseIn(pingPin, HIGH);
     
     int distanceInchesA = microsecondsToInches(aroutecheck);// convert the time into a distance
      
      Serial.print(distanceInchesA);// displays distance in inches
      Serial.print("In. dist route A,");
      Serial.println();
  
   return distanceInchesA;//returns data collected
   delay(1);
  
   
 }

//..................................new function.......................//

int pingBroute()// ping route B
  {
    
    myservopan.write(155);  //Pan servo to route B
    
    delay(1000);// delay to allow pan to complete
    
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
    pinMode(pingPin, INPUT);
    delayMicroseconds(1);
      int  broutecheck = pulseIn(pingPin, HIGH);
      
      int distanceInchesB = microsecondsToInches(broutecheck);// convert the time into a distance
        Serial.print(distanceInchesB);// displays distance in inches
        Serial.print("In. dist route B");
        Serial.println();
        return distanceInchesB;
        delay(1);
  }

//..................................new function.......................//

int turnA()
  {
         analogWrite (E1,255);
         digitalWrite(M1,LOW);
         analogWrite (E2,255);
         digitalWrite(M2,HIGH);
         Serial.print("turn a");
         Serial.println("");
       delay(2000); //delay time allows for 90 degree turn
   }

//..................................new function.......................//

int turnB()
  {    
         analogWrite (E1,255);
         digitalWrite(M1,HIGH);
         analogWrite (E2,255);
         digitalWrite(M2,LOW);
         Serial.print("Turn B");
         Serial.println("");
       delay(2000); //delay time allows for 90 degree turn
      
   }
//..................................new function.......................//

int reverse()//REV motion
  { 
    analogWrite (E1,255);
    digitalWrite(M1,LOW);
    analogWrite (E2,255);
    digitalWrite(M2,LOW);
    Serial.print("REV");
    Serial.println("");
    delay(2000);
  }
