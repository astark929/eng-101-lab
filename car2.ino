
#include <Servo.h>
#include <Wire.h>
#include "SparkFun_Qwiic_Joystick_Arduino_Library.h"

//motor pins and speed
/*
default pins for motors:
2 = direction for A
3 = speed control for A
4 = direction for B
11 = speed control for B

alertnet pins for motors:
8 = direction for A
9 = speed control for A
7 = direction for B
10 = speed control for B

NOTE: when plugging in the motors
the charge varies. 
generally the layout when the pins are facing you are
blue lights next to the motor pins.
+ - + -, when no blue lights on
+ - - +, when one blue light is on
- + - +, when both blue lights are on
*/
#define f 0 //forward or clockwise
#define r 1 //reverse or counter-clockwise
#define motor1 0
#define motor2 1

int speed = 150; 
//i believe int and byte should work
//the same way here 
const byte sc1 = 3;
const byte sc2 = 11;
const byte d1 = 12;
const byte d2 = 13;
/*
#define d1 2 // direction motor A
#define sc1 3  // speed control for motor A
#define d2 4 // direction for motor B
#define sc2 11 // speed control for motor B
*/

//servor universal variables
//may need
//#define serv1 d1
const int SPin = 7;
//original was 9;
Servo servo; 

int clawstate = 0; // 0 = open, 1 = closed
int buttonval = 0;
//Servo servo2;  //if i need another servo

//sensor universal variables
//#define triggerpin d9
//#define echopin d10
const int triggerPin = 5;
const int echoPin  = 6;
float distance = 0;

//extra stuff
int val = 0;
const uint8_t output = OUTPUT;
const uint8_t input  = INPUT;
const uint8_t high = HIGH;
const uint8_t low  = LOW;

//joystick variables
int mapvalV = 0;
int mapvalH = 0;
JOYSTICK joystick;

//variables for autonomous stuff
int state = 0;
bool paused = false;
unsigned long pasusedat = 0;

unsigned long timestate  = 0;
unsigned long t = millis();


void setup() {
  setupArdumoto();
}
/**/
void loop(){

}
//*/
/*
void loop(){
  drive(motor1, 200);
  drive(motor2 100);
  delay(5000);
  stopped();
  while(true){}
}
//*/

//motor methods
void left(){
  drive(motor1, 255);
  drive(motor2, 0);
}
void left(int s){
  drive(motor1, 255);
  drive(motor2, s);
}
void left(int s, int s2){
  drive(motor1, s);
  drive(motor2, s2);
}

void right(){
  drive(motor1, 0);
  drive(motor2, 255);
}
void right(int s){
  drive(motor1, 0);
  drive(motor2, s);
}
void right(int s, int s2){
  drive(motor1, s2);
  drive(motor2, s);
}

void forward(){
  drive(motor1, 255);
  drive(motor2, 255);
}
void forward(int s){
  drive(motor1, s);
  drive(motor2, s);
}

void backwards(){
  drive(motor1, 255);
  drive(motor2, 255);
}
void backwards(int s){
  drive(motor1, s);
  drive(motor2, s);
}

void drive(byte motor, byte spd)
{
  if (motor == motor1)
  {
    rmotor1(spd);
  }
  else if (motor == motor2)
  {
    rmotor2(spd);
  }  
}
void rmotor1(int speed){
  if(speed > 0){
    digitalWrite(d1, f);
  }
  else if (speed < 0){
    digitalWrite(d1, r);
  }
  else{
      digitalWrite(d1, 0);
      analogWrite(sc1, 0);
    }
  analogWrite(sc1, abs(speed));
}

void rmotor2(int speed){
  if(speed > 0){
    digitalWrite(d2, f);
  }
  else if (speed < 0){
    digitalWrite(d2, r);
  }
  else{
      digitalWrite(d2, 0);
      analogWrite(sc2, 0);
    }
  analogWrite(sc2, abs(speed));
}
void stopped()
{
  drive(motor1, 0);
  drive(motor2, 0);
}
void stopped(byte motor)
{
  drive(motor, 0);
}
void motortest(){
  forward();
  delay(3000);
  forward(2);
  delay(3000);

  left();
  delay(3000);
  left(2);
  delay(3000);
  left(2, 10);
  delay(3000);

  right(2, 10);
  delay(3000);

  backwards();
  backwards(10);

}
void setupArdumoto()
{
  pinMode(sc1, output);
  pinMode(sc2, output);
  pinMode(d1, output);
  pinMode(d2, output);

  digitalWrite(sc1, low);
  digitalWrite(sc2, low);
  digitalWrite(d1, low);
  digitalWrite(d2, low);

  sensorsetup();
  serveroSetup();
}

//sensor methods
void sensorsetup(){
  pinMode(triggerPin, output);
  pinMode(echoPin, input);
}

float getdistance(){
  float time;
  float cd;

  digitalWrite(triggerPin, high);
  delayMicroseconds(10);
  digitalWrite(triggerPin, low);
  time = pulseIn(triggerPin, low);
  cd = time / 148.0; //calcs a distance in inch
  //cd = time / 58; // calcs a distance in cm
  return cd; //should return a value in inch
}
void checkobj(){
  if(getdistance < 3){
    stopped();
    delay(1000);
    backwards(10);
    delay(1000);
    stopped();
  }
}
bool object(){
  if(getdistance < 3){
    return true;
  }
  else {  
    return false;
  }
}

//servo methods
void serveroSetup(){
  servo.attach(SPin);
}
void Sleft(){
  servo.write(45);
}
void Sright(){
  servo.write(135);
}
void Scenter(){
  servo.write(90);
}
void Sangle(int a){
  servo.write(a);
}
void Sangle(Servo &srv, int a){
  srv.write(a);
}
//for teammates, this method grabs the object (servo kind)
//and moves that servo accordingly by the value of a

void groundcheck(){
  if(getdistance() > 2){
    stopped();
    delay(1000);
    backwards(100);
    delay(1000);
    stopped();
  }
}
void clawgrab(){
  Sangle(servo, 45);
}
void clawrelease(){
  Sangle(servo, 90);
}

//joystick methods
void movejoystick(){
  int joyh = joystick.getHorizontal();
  int joyv = joystick.getVertical();
  int joyb = joystick.getButton(); 
  //if holding down joystick makes joyb = 1, if released = 0

  int x = map (joyh, 0, 1023, -255, 255); //horizontal
  int y = map (joyv, 0, 1023, -255, 255); //vertical

  /*
  //if drift occurs use
  if(abs(y) < 30) y = 0;
  if(abs(x) < 30) x = 0;
  */

  int motora = x+y;
  int motorb = y-x;
  motora = constrain(motora, -255, 255);
  motorb = constrain(motorb, -255, 255);

  rmotor1(motora);
  rmotor2(motorb); 

  if(joyb == 1 && buttonval == 0){
    if(clawstate == 0){
      clawgrab();
      clawstate = 1;
    }
    else if(clawstate == 1){
      clawrelease();
      clawstate = 0;
    }
  }


}

//autonomous mode
void automode(){
  if(object()){
    if(!paused){
      paused = true;
      pasusedat = millis();
    }
    backwards(100);
    delay(1000);
    return;
  }
  if(paused && !object()){
    unsigned long duration = millis() - pasusedat;
    timestate += duration;
    paused = false;
  }
  /*
  rmember to add a case statement that will grab the payload
  and another case at the end that will release the payload
  */
  switch (state){
    case 0:
    if(millis() - timestate < 2000 && state == 0){
      forward();
    }
    else {
      stopped();
      state = 1;
      timestate = millis();
    }
    break;

    case 1:
      if(millis() - timestate < 800 && state == 1){
        left();
      }
      else{
        stopped();
        state = 2;
        timestate = millis();
      }
    break;

    case 2:
    if(millis() - timestate < 2000 && state == 2){
      forward(100);
    }
    else{
      stopped();
      state = 3;
      timestate = millis();
    }
    break;

    case 3:
    if(millis() - timestate < 2000 && state == 3){
      right(100);
    }
    else{
      stopped();
      state = 4;
      timestate = millis();
    }
    break;

    case 4:
    if(millis() - timestate < 4000 && state == 4){
      forward(100);
    }
    else{
      stopped();
      state = 5;
      timestate = millis();
    }
    break;

    default:
      stopped();
      while(true){}
  }
}

