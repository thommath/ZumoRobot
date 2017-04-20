
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
#define rxPin 2  // Rx pin on Bluetooth unit
//#define musicPin A5
#define servoPin 3


#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <SoftwareSerial.h>
#include <PLabBTSerial.h>
#include <SpacebrewYun.h>

#include "imperial.h"
#include "eyes.h"

//PLabBTSerial btSerial(txPin, rxPin);


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
ZumoReflectanceSensorArray reflectanceSensors(QTR_NO_EMITTER_PIN);
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

//MUSIC
//Music music (musicPin);

//Eyes
Sonar eyesBaby (servoPin); 




//State! What the f are we doing right now?
int state;
//When did we change our state last time?
long timeall = 0;
//How fast are we going?
int velocity;


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


void calibrate(){
  //Basic calibration for color sensors
  delay(1000);
  int i;
  for(i = 0; i < 80; i++){
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
}

/*
 * 
 * Bluetooth
 * 
 */

/*
void waitForStart(){
  String message = "";
  while(!message.equals("Start")){
    trySetSettings();
    delay(100);
  }
}


void trySetSettings(){
  trySetSettings(btRecieve());
}

void trySetSettings(String message){
  if(!message.equals("")){
    setSettings(message);
  }
}


String btRecieve(){
  int availableCount = btSerial.available();
  //Bluetooth recieve
  if (availableCount > 0) {
    char text[availableCount];
    btSerial.read(text, availableCount);
    return String(text);
  }
  return "";
}


void setSettings(String text){
  String temp = "";
  for(int n = 0; n < text.length(); n++){
    if(text[n] == ' '){
      velocity = temp.toInt();
      print("Set velocity to " + String(velocity) + " " + temp);
      temp = "";
    }
    temp += text[n];
  }
  constantTurnTime = temp.toInt();
  print("Set constantTurnTime to " + String(constantTurnTime));
}*/

/*
 * 
 * Print functions
 * 
 */

void print(String s){
  Serial.println(s);
//  btSerial.println(s);
}


void print(String s, int i){
  Serial.print(s);
  Serial.println(i);
//  btSerial.print(s);
//  btSerial.println(i);
}

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
//  btSerial.begin(9600); // Open serial communication to Bluetooth unit
  print("Booting...");

  
  eyesBaby.beginning();

//  music.init();
  reflectanceSensors.init();


  //Setting default values
  state = 0;
  velocity = 250;
  constantTurnTime = 3700;
  
  

  print("Press button for calibration");
  button.waitForButton();
  calibrate();


  print("\nPress button for fight");
  button.waitForButton();

  //TODO wait for go signal from phone
//  waitForStart();

  print("Fight!");

}

/* 
 *  
 *  *
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
 
  //music.play();
  //print(music.getStuff());


  //Read sensor data
  unsigned int sensors[6];
  reflectanceSensors.readLine(sensors);
  eyesBaby.reads();
  
  //Update state based on sensor data
  updateState(sensors);
  
  //Set motor speeds based on the state and the state timer (cliffhanger)
  setMotorSpeeds();
  
  
  //TODO? Maybe do this in setup instead?
//  trySetSettings();
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
void updateState(unsigned int *sensors){
/*  print(String(sensors[0]) + " " + 
        String(sensors[1]) + " " + 
        String(sensors[2]) + " " + 
        String(sensors[3]) + " " + 
        String(sensors[4]) + " " + 
        String(sensors[5])); */
  //Find state
  if (sensors[0] < 800 && sensors[5] < 800) {
    //at the edge! go backwards!
    state = 1;
    timeall = millis();
    print("1");
  }
  else if (sensors[0] < 800 && state < 1) {
    //left side hit white, so turn right
    state = 3;
    timeall = millis();
    print("2");
  }
  else if (sensors[5] < 800 && state < 1) {
    //right side hit white, so turn left
    state = 2;
    timeall = millis();
    print("3");
  }
  else if(eyesBaby.rightEye && state == 0){
    state = 6;
    timeall = millis();
    print("6");
  }
  
  if(eyesBaby.frontEye && (state == 0 || state == 6)){
    state = 4;
    timeall = millis();
    print("4");
  }else if(!eyesBaby.frontEye && state == 4){
    state = 0;
  }

  
}

//Sets motor speeds based on state and the state time (cliffhanger)
void setMotorSpeeds(){
//  print(String(state) + " " + String(cliffhanger));
  int speeds[2];

  switch(state){
   case 0: case0(speeds); break;
   case 1: case1(speeds); break;
   case 2: case2(speeds); break;
   case 3: case3(speeds); break;
   case 4: case4(speeds); break;
   case 5: case5(speeds); break;
   case 6: case6(speeds); break;
  }
  
  //Set motor speed
  motors.setSpeeds(speeds[0], speeds[1]);
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
  if(millis() - timeall < 150){

    getTurnSpeeds(speeds, 0, -velocity, true);

  }else if(millis() - timeall < 150 + getTurnTime(2*pi, velocity, 100)){

    getTurnSpeeds(speeds, 100, velocity, true);

  }else{
    state = 0;
  }
}

//A fowl wind reeks from the west
void case2(int *speeds){
  if(millis() - timeall < getTurnTime(2*pi/3, velocity, 70)){

    getTurnSpeeds(speeds, 80, -velocity, false);

  }else{
    state = 0;
  }
}

//A fowl wind reeks from the east
void case3(int *speeds){
/*  if(millis() - timeall < getTurnTime(2*pi/3, velocity, 70)){

    getTurnSpeeds(speeds, 70, -velocity, false);

  }else{
    state = 0;
  }*/
  if(millis() - timeall < getTurnTime(2*pi/3, velocity, 70)){

    getTurnSpeeds(speeds, 80, -velocity, false);

  }else{
    state = 0;
  }
}

// Enemy in sight, take action
void case4(int *speeds){
  if(millis() - timeall < 200){

    getTurnSpeeds(speeds, 10, 600, false);

  }else if(millis() - timeall < 400){

    getTurnSpeeds(speeds, 10, 600, true);

  }else{
    timeall = millis();
  }
  
}

//searching for enemy
void case5(int *speeds){
  getTurnSpeeds(speeds, 100, 100, false);
}

//Enemy at the right
void case6(int *speeds){
  if(millis() - timeall < 300){
    
    getTurnSpeeds(speeds, 40, 250, true);
  
  }else if(millis() - timeall < 300 + getTurnTime(3*pi, velocity, 70)){
  
    getTurnSpeeds(speeds, 90, 250, true);
  
  }else if(millis() - timeall < 300 + 2*getTurnTime(3*pi, velocity, 70)){
  
    getTurnSpeeds(speeds, 90, 250, false);
  
  }else{
    state = 0;
  }
}




