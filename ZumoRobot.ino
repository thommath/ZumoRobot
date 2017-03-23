#include <SpacebrewYun.h>

/*
 * 
 *  _    _ _____ _     _____ ________  ___ _____ _ 
 * | |  | |  ___| |   /  __ \  _  |  \/  ||  ___| |
 * | |  | | |__ | |   | /  \/ | | | .  . || |__ | |
 * | |/\| |  __|| |   | |   | | | | |\/| ||  __|| |
 * \  /\  / |___| |___| \__/\ \_/ / |  | || |___|_|
 *  \/  \/\____/\_____/\____/\___/\_|  |_/\____/(_)
 * 
 * 
 * We have one rule here: 
 * Do what you want except one thing, never use delay! 
 * 
 */

#define txPin 6  // Tx pin on Bluetooth unit
#define rxPin 3  // Rx pin on Bluetooth unit


#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>


#define trigPin PIN_A4
#define echoPin PIN_A1


//#include "imperial.h"

PLabBTSerial btSerial(txPin, rxPin);



/*
 * 
 *  _   _  _____ _     ______ ___________    ______ _   _ _   _ _____ _____ _____ _____ _   _  _____ 
 * | | | ||  ___| |    | ___ \  ___| ___ \   |  ___| | | | \ | /  __ \_   _|_   _|  _  | \ | |/  ___|
 * | |_| || |__ | |    | |_/ / |__ | |_/ /   | |_  | | | |  \| | /  \/ | |   | | | | | |  \| |\ `--. 
 * |  _  ||  __|| |    |  __/|  __||    /    |  _| | | | | . ` | |     | |   | | | | | | . ` | `--. \
 * | | | || |___| |____| |   | |___| |\ \    | |   | |_| | |\  | \__/\ | |  _| |_\ \_/ / |\  |/\__/ /
 * \_| |_/\____/\_____/\_|   \____/\_| \_|   \_|    \___/\_| \_/\____/ \_/  \___/ \___/\_| \_/\____/ 
 * 
 * 
 */

float constantTurnTime = 1500;
float pi = 3.141592653589793238;
 
//Sets motor speeds depending on turnRate and velocity
void getTurnSpeeds(int *speeds, int turnRate, int velocity, boolean dir){
  if (dir){
    speeds[1] = int(((-turnRate+50)/50.0)*velocity);
    speeds[0] = velocity;
    return;
  }
  speeds[0] = int(((-turnRate+50)/50.0)*velocity);
  speeds[1] = velocity;
}

//Returns how long you need to turn for to get the angle you want depending on the turnRate, maxSpeed and angle
float getTurnTime(int angle, int maxSpeed, float turnRate){
  return angle*constantTurnTime/(turnRate*maxSpeed/500.0);
}


void print(String s){
  Serial.println(s);
  btSerial.print(s);
}

/*
 * 
 *  _____  _     ___________  ___   _         _   _  ___  ______ _____  ___  ______ _      _____ _____ 
 * |  __ \| |   |  _  | ___ \/ _ \ | |       | | | |/ _ \ | ___ \_   _|/ _ \ | ___ \ |    |  ___/  ___|
 * | |  \/| |   | | | | |_/ / /_\ \| |       | | | / /_\ \| |_/ / | | / /_\ \| |_/ / |    | |__ \ `--. 
 * | | __ | |   | | | | ___ \  _  || |       | | | |  _  ||    /  | | |  _  || ___ \ |    |  __| `--. \
 * | |_\ \| |___\ \_/ / |_/ / | | || |____   \ \_/ / | | || |\ \ _| |_| | | || |_/ / |____| |___/\__/ /
 *  \____/\_____/\___/\____/\_| |_/\_____/    \___/\_| |_/\_| \_|\___/\_| |_/\____/\_____/\____/\____/ 
 * 
 * 
 */

//Define sensors
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

//MUSIC
//Music music (3);


//State! What the f are we doing right now? 
int state;
//Cliffhanger, for how long have we been in this state? 
int cliffhanger;
//How fast are we going? 
int velocity;

/*
 *  
 *  _____ _____ _____ _   _______ 
 * /  ___|  ___|_   _| | | | ___ \
 * \ `--.| |__   | | | | | | |_/ /
 *  `--. \  __|  | | | | | |  __/ 
 * /\__/ / |___  | | | |_| | |    
 * \____/\____/  \_/  \___/\_|   
 * 
 * 
 */

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600); // Open serial communication to Bluetooth unit  
  print("Booting...");

  //music.init();
  reflectanceSensors.init();

  //Setting default values
  state = 0;
  cliffhanger = 0;
  velocity = 200;

  //setup buttSensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //TODO: make a loop for config from processing
  

  print("Press button for calibration");
  button.waitForButton();


  //Basic calibration for color sensors
  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
      
    reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0);


  
  print("\nPress button for fight");
  button.waitForButton();

  print("Fight!");

}

/*
 *  
 *  _     _____  ___________ 
 * | |   |  _  ||  _  | ___ \
 * | |   | | | || | | | |_/ /
 * | |   | | | || | | |  __/ 
 * | |___\ \_/ /\ \_/ / |    
 * \_____/\___/  \___/\_|                            
 * 
 * 
 */

void loop()   // Draw a triangle. 45, 90, 45 degrees...
{

  //buttSensor kode:
  checkBehind();

  //music.play();
  //print(music.getStuff());

  //Read sensor data
  //0 = left, 5 = right
  unsigned int sensors[6];
  reflectanceSensors.readLine(sensors);

  //Update state based on sensor data
  updateState(sensors);

  print("state " + String(state));

  
  //Set motor speeds based on the state and the state timer (cliffhanger)
  setMotorSpeeds();
  
  
  //Default delay
  delay(10);
  //Increment the state time counter
  cliffhanger++;
}

/*
 *  
 *  _____ _____ _   _ ___________ _____ _        ______ _   _ _   _ _____ _____ _____ _____ _   _  _____ 
 * /  __ \  _  | \ | |_   _| ___ \  _  | |       |  ___| | | | \ | /  __ \_   _|_   _|  _  | \ | |/  ___|
 * | /  \/ | | |  \| | | | | |_/ / | | | |       | |_  | | | |  \| | /  \/ | |   | | | | | |  \| |\ `--. 
 * | |   | | | | . ` | | | |    /| | | | |       |  _| | | | | . ` | |     | |   | | | | | | . ` | `--. \
 * | \__/\ \_/ / |\  | | | | |\ \\ \_/ / |____   | |   | |_| | |\  | \__/\ | |  _| |_\ \_/ / |\  |/\__/ /
 *  \____/\___/\_| \_/ \_/ \_| \_|\___/\_____/   \_|    \___/\_| \_/\____/ \_/  \___/ \___/\_| \_/\____/ 
 * 
 * 
 */

//Changes state based on sensor data
void updateState(int *sensors){
  //Find state
  
  if (sensors[0] < 800 && sensors[5] < 800) {
    //at the edge! go backwards!
    state = 1;
    cliffhanger = 0; 
  }
  else if (sensors[0] < 800 && state < 1) {
    //left side hit white, so turn right
    state = 2;
    cliffhanger = 0;
  }
  else if (sensors[5] < 800 && state < 1) {
    //right side hit white, so turn left
    state = 3;
    cliffhanger = 0;
  }
  //Check behind
  else if(checkBehind() == true){
    state = 4;
    cliffhanger = 0;
  }
}

//Sets motor speeds based on state and the state time (cliffhanger)
void setMotorSpeeds(){
  unsigned int speeds[2];

  switch(state){
   case 0: case0(speeds); break;
   case 1: case1(speeds); break;
   case 2: case2(speeds); break;
   case 3: case3(speeds); break;
   case 4: case4(speeds); break;
  }
  //Set motor speed
  motors.setSpeeds(speeds[0], speeds[1]);
}

boolean checkBehind(){
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance <= 6){
    Serial.println("butt=true");
    return true;
  }
  else {
    //Serial.print("Distance = ");
    //Serial.print(distance);
    //Serial.println(" cm");
    //Serial.println("butt=false");
    return false;
  }
}
/*
 *  
 *  _____   ___   _____ _____ _____ 
 * /  __ \ / _ \ /  ___|  ___/  ___|
 * | /  \// /_\ \\ `--.| |__ \ `--. 
 * | |    |  _  | `--. \  __| `--. \
 * | \__/\| | | |/\__/ / |___/\__/ /
 *  \____/\_| |_/\____/\____/\____/ 
 * 
 * 
 */


/*
 * HOW TO MAKE A NEW CASE:
 * 
 * first you make the function here: 

void caseX(int *speeds){
  if(cliffhanger < (time if you go striaight (usually 100-500) or getTurnTime(angle in rad, speed 0-500, how sharp turn 0-100 where 0 is straight and 100 is turn on the spot){
  
    getTurnSpeed(speeds, how sharp you turn that is THE SAME AS ABOVE, speed that is THE SAME AS ABOVE, and true for right and false for left I think);
  
  }else if(cliffhanger < the time + the new time){
  
    getTurnSpeed(speeds, ...);
  
  }else{
    state = nextState;
    cliffhanger = 0;
  }
}

 * 
 */
 
//Booring
void case0(int *speeds){
  getTurnSpeeds(speeds, 0, velocity, true);
}

//You have reached the end of the known world, here be monsters! 
void case1(int *speeds){
  if(cliffhanger < 10){
    
    getTurnSpeeds(speeds, 0, -velocity, true);
  
  }else if(cliffhanger < 10 + getTurnTime(pi, velocity, 100)){
  
    getTurnSpeeds(speeds, 100, velocity, true);
  
  }else{
    state = 0;
    cliffhanger = 0;
  }
}

//A fowl wind reeks from the west
void case2(int *speeds){
  if(cliffhanger < getTurnTime(2*pi/3, velocity, 70)){
  
    getTurnSpeeds(speeds, 100, velocity, true);
  
  }else{
    state = 0;
    cliffhanger = 0;
  }
}

//A fowl wind reeks from the east
void case3(int *speeds){
  if(cliffhanger < getTurnTime(2*pi/3, velocity, 70)){
  
    getTurnSpeeds(speeds, 100, velocity, false);
  
  }else{
    state = 0;
    cliffhanger = 0;
  }
}
// Enemy behind, take evatise action
void case4(int *speeds){
  if(cliffhanger < 100){
    
    print("We're being fucked in our ASSES!");
    getTurnSpeeds(speeds, 0, 0, false);
    delay(5000);
    state = 0;
    
  }else{
    state = 0;
    cliffhanger = 0;
  }
}


