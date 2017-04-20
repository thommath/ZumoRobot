#include <NewPing.h>
#include "RunningMedian.h"
#include <math.h>
 
#include <Arduino.h>

#define SONAR_NUM 2 // Number of sensors



class Sonar{
  
//  Servo myservo; //servo object
    
  //int servoAngle = 0; // global variable to store the servo position

//  long timeServo = 0;
//  byte servoDir = 1, servoAngle = 90;

  //Forward eye
  const int echoPin = A5;
  const int triggerPin = A1;
  const int echoPin2 = 6;
  const int triggerPin2 = 2;
  int teller[2] = {0, 0};

  
  RunningMedian dists[2] = {RunningMedian(15), RunningMedian(15)};
  int distance[2];
  const int maxDistance = 100;
  uint8_t currentSensor = 0; // which sensor is active
  
  /* http://playground.arduino.cc/Code/NewPing */
  
  NewPing sonar[SONAR_NUM] = { // liste med sensorer
    NewPing(triggerPin, echoPin, maxDistance),
    NewPing(triggerPin2, echoPin2, maxDistance)
  };

  int superPin;
  
 //Oppretter et sonar-objekt
  public:

  boolean frontEye = false;
  boolean rightEye = false;
   
    Sonar(int pin) {
      //Du åpner Serial Monitor ved å trykke Ctrl + Shift + M 
      
      superPin = pin;    
    }

    void beginning(){
      Serial.begin(9600); //Her blir Serial monitor aktivert slik at Arduino kan skrive info til PCen
      pinMode(superPin,OUTPUT);
//      myservo.attach(superPin); // attaches the servo on pin 9
    }
    
    
    void reads() {

   //   search();
      getDist(0);
      getDist(1);
   
      if (teller[0] == 0) {
        frontEye = someoneThere(0);
      }
      if (teller[1] == 0) {
        rightEye = someoneThere(1);
      }
      
      teller[0]++;
      teller[1]++;
      
    }
/*    
    void search() {  
          if (millis() - timeServo > 5){
            if(servoAngle >= 0 || servoAngle <= 179){
              if(servoAngle <= 0){
                servoDir = 1;
              } else if (servoAngle >= 179) {
                servoDir = -1;
              }
              servoAngle += servoDir;
              myservo.write(servoAngle);
              if(servoAngle % 10 == 0){
                Serial.println("Servo angle : " + String(servoAngle));
              }
              timeServo = millis();
            }
            
        }
        
      }
    

   */

   int ant[2] = {1, 1};
    
    
    void getDist(uint8_t d){
      if (teller[d] == 0) {
          dists[d] = RunningMedian(ant[d]);
      } else if (teller[d] >= ant[d]*1) {        
        distance[d] = dists[d].getMedian();
        teller[d] = 0;
      }
      if ( teller[d] % 1 == 0) {
        unsigned int time = sonar[d].ping();
        long x = sonar[d].convert_cm(time);
        dists[d].add(x);
      }
    }
    
    boolean someoneThere(uint8_t d){
      int total = 0;
    //  for (int i=0;i<5;i++){
         total += distance[d];  
    //  }
       if(total>0 && total<70){
         Serial.println("true" + String(d));
//         Serial.println(distance);
        return true;
       }
       Serial.println("false" + String(d));
//       Serial.println(distance);
      return false;
    }
};
