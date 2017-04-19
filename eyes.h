#include <NewPing.h>
#include "RunningMedian.h"
#include <math.h>
 
#include <Arduino.h>

#define SONAR_NUM 1 // Number of sensors





class Sonar{
  
//  Servo myservo; //servo object
    
  //int servoAngle = 0; // global variable to store the servo position

//  long timeServo = 0;
//  byte servoDir = 1, servoAngle = 90;

  //Forward eye
  const int echoPin = A5;
  const int triggerPin = A1;
  int teller = 0;

  
  RunningMedian dists = RunningMedian(15);
  int distance;
  const int maxDistance = 100;
  uint8_t currentSensor = 0; // which sensor is active
  
  /* http://playground.arduino.cc/Code/NewPing */
  
  NewPing sonar[SONAR_NUM] = { // liste med sensorer
    NewPing(triggerPin, echoPin, maxDistance)
  };

  int superPin;
  
 //Oppretter et sonar-objekt
  public:

  boolean frontEye = false; 
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
      
      if (teller == 0) {
        frontEye = someoneThere(0);
      }
      
      teller++;
      
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
       if(total>0 && total<70){
         Serial.println("true");
//         Serial.println(distance);
        return true;
       }
       Serial.println("false");
//       Serial.println(distance);
      return false;
    }
};
