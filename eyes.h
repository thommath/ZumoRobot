#include <NewServo.h>
#include <Ping.h>
#include "RunningMedian.h"
#include <math.h>
//#include <Servo.h>

#include <Arduino.h>

#define SONAR_NUM 2 // Number of sensors





class Sonar{
  
  NewServo myservo; //servo object
    
  //int servoAngle = 0; // global variable to store the servo position

  long timeServo = 0;
  byte servoDir = 1, servoAngle = 0;

  //Forward eye
  const int echoPin = A0;
  const int triggerPin = A1;
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
  
  Ping sonar[SONAR_NUM] = { // liste med sensorer
    Ping(triggerPin, echoPin, maxDistance),
    Ping(triggerPinB, echoPinB, maxDistanceB)
  };

  int superPin;
  
 //Oppretter et sonar-objekt
  public:

    boolean frontEye = false;
    boolean backEye = false;

    boolean refresh = false;
  
    Sonar(int pin) {
      //Du åpner Serial Monitor ved å trykke Ctrl + Shift + M 
      superPin = pin;    
    }

    void beginning(){
      Serial.begin(9600); //Her blir Serial monitor aktivert slik at Arduino kan skrive info til PCen
      pinMode(superPin,OUTPUT);
      myservo.attach(superPin); // attaches the servo on pin designated by superPin
    }
    
    
    void reads() {
      search();
      getDist(0);
      getDist(1);
      
      if (teller == 0) {
        frontEye = someoneThere(0);
        backEye = someoneThere(1);
      }
      
      teller++;
      
    }
    
    void search() {        
      if (millis() - timeServo > 1){
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
          //refresh = refresh ? false : true;
          //if(refresh) SoftwareServo::refresh();
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
        sonar[d].fire();
        long x = sonar[d].inches();
        dists.add(x);
      }
    }
    
    boolean someoneThere(uint8_t d){
      int total = 0;
      total += distance;  
      if(total>0){
        Serial.println("true");
        Serial.println(distance);
        return true;
      }
      Serial.println("false");
      Serial.println(distance);
      return false;
    }
};
