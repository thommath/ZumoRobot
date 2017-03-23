#include <NewPing.h>
#include "RunningMedian.h"
#include <math.h>
#include <Servo.h>
 
#include <Arduino.h>

#define SONAR_NUM 1 // Number of sensors

Servo myservo; //servo object

//int servoAngle = 0; // global variable to store the servo position
long timeServo = 0;
byte servoDir = -1, servoAngle = 0;

const int echoPin = 2;
const int triggerPin = 4;
int teller = 0;

RunningMedian dists = RunningMedian(15);
int distance;
const int maxDistance = 100;
uint8_t currentSensor = 0; // which sensor is active

/* http://playground.arduino.cc/Code/NewPing */

NewPing sonar[SONAR_NUM] = { // liste med sensorer
  NewPing(triggerPin, echoPin, maxDistance)//,
  //NewPing(triggerPin, echoPin, maxDistance),
  //NewPing(triggerPin, echoPin, maxDistance),
  //NewPing(triggerPin, echoPin, maxDistance) 
};
 //Oppretter et sonar-objekt

void setup() {
  //Du åpner Serial Monitor ved å trykke Ctrl + Shift + M 
  Serial.begin(9600); //Her blir Serial monitor aktivert slik at Arduino kan skrive info til PCen
  myservo.attach(9); // attaches the servo on pin 9
}


void loop() {
  
  getDist(0);
  //search();
  
  if (teller == 0) {
    someoneThere(0);
  }
  
  teller++;
  delay(10);
}

void search() {  
      if (millis() - timeServo > 1){
        if(servoAngle >= 0 || servoAngle <= 179){
          if(servoAngle == 0){
            servoDir = 1;
          } else if (servoAngle == 179) {
            servoDir = -1;
          }
          servoAngle += servoDir;
          myservo.write(servoAngle);
          timeServo = millis();
        }
        
    }
    
  }




void getDist(uint8_t d){
  if (teller == 0) {
      dists = RunningMedian(15);
  } else if (teller >= 15*1) {        
    distance = dists.getMedian();
    teller = 0;
  }
  if ( teller % 1 == 0) {
    unsigned int time = sonar[d].ping();
    long x = sonar[d].convert_cm(time);
    dists.add(x);

  }

  
}

boolean someoneThere(uint8_t d){
  int total = 0;
//  for (int i=0;i<5;i++){
     total += distance;  
//  }
   if(total>0){
   Serial.println("true");
   Serial.println(distance);
    return true;
   }
   Serial.println("false");
   Serial.println(distance);
  return false;
}

