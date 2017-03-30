#include <NewPing.h>
#include "RunningMedian.h"
#include <math.h>
#include <Servo.h>
 
#include <Arduino.h>

#define SONAR_NUM 2 // Number of sensors

class Sonar{
  Servo myservo; //servo object
  
  //int servoAngle = 0; // global variable to store the servo position
  long timeServo = 0;
  byte servoDir = -1, servoAngle = 0;

  //Forward eye
  const int echoPin = A1;
  const int triggerPin = A2;
  int teller = 0;

  //Backwards eye
  const int echoPinB = A3;
  const int triggerPinB = A4;

  
  RunningMedian dists = RunningMedian(15);
  int distance;
  const int maxDistance = 100;
  const int maxDistanceB = 6;
  uint8_t currentSensor = 0; // which sensor is active
  
  /* http://playground.arduino.cc/Code/NewPing */
  
  NewPing sonar[SONAR_NUM] = { // liste med sensorer
    NewPing(triggerPin, echoPin, maxDistance),
    NewPing(triggerPinB, echoPinB, maxDistanceB)
  };
  
 //Oppretter et sonar-objekt
  public:
    void Sonar() {
      //Du åpner Serial Monitor ved å trykke Ctrl + Shift + M 
      Serial.begin(9600); //Her blir Serial monitor aktivert slik at Arduino kan skrive info til PCen
      myservo.attach(9); // attaches the servo on pin 9
    }
    
    
    void reads() {
      
      getDist(0);
      getDist(1);
      //search();
      
      if (teller == 0) {
        boolean frontEye = someoneThere(0);
        boolean backEye = someoneThere(1);
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
}
