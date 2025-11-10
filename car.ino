//NOT FINISHED
#include <Servo.h>

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
#define f 0 //forward
#define r 1 //reverse
#define motor1 0
#define motor2 1

int speed = 150; 

const int sc1 = 3;
const int sc2 = 11;
const int d1 = 2;
const int d2 = 4;

//servor universal variables
//may need
#define serv1 d1
Servo servo; 

//sensor universal variables

//#define triggerpin d9
//#define echopin d10
const int triggerPin = 9;
const int echoPin  = 10;
float distance = 0;

//extra stuff
int val = 0;
const uint8_t output = OUTPUT;
const uint8_t input  = INPUT;
const uint8_t high = HIGH;
const uint8_t low  = LOW;



void setup() {
  setupArdumoto();
}

void loop(){
  stopped();
}


//motor methods
void left(){
  driveArdumoto(motor1, f, 255);
  driveArdumoto(motor2, f, 0);
}
void left(int b){
  driveArdumoto(motor1, f, 255);
  driveArdumoto(motor2, r, b);
}
void left(int b, int s){
  driveArdumoto(motor1, f, s);
  driveArdumoto(motor2, r, b);
}

void right(){
  driveArdumoto(motor1, f, 0);
  driveArdumoto(motor2, f, 255);
}
void right(int b){
  driveArdumoto(motor1, r, b);
  driveArdumoto(motor2, f, 255);
}
void right(int b, int s){
  driveArdumoto(motor1, r, b);
  driveArdumoto(motor2, f, s);
}

void forward(){
  driveArdumoto(motor1, f, 255);
  driveArdumoto(motor2, f, 255);
}
void forward(int s){
  driveArdumoto(motor1, f, s);
  driveArdumoto(motor2, f, s);
}

void backwards(){
  driveArdumoto(motor1, r, 255);
  driveArdumoto(motor2, r, 255);
}
void backwards(int s){
  driveArdumoto(motor1, r, s);
  driveArdumoto(motor2, r, s);
}

void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == motor1)
  {
    digitalWrite(d1, dir);
    analogWrite(sc1, spd);
  }
  else if (motor == motor2)
  {
    digitalWrite(d2, dir);
    analogWrite(sc2, spd);
  }  
}

void stopped()
{
  driveArdumoto(motor1, 0, 0);
  driveArdumoto(motor2, 0, 0);
}
void stopped(byte motor)
{
  driveArdumoto(motor, 0, 0);
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
}

//sensor methods
void sensorsetup(){
  pinMode(triggerpin, output);
  pinMode(echopin, input);
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
  if(getdistance < 1){
    backwards(10);
  }
}


