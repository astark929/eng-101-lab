//NOT FINISHED
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

int speed = 150; 

const int sc1 = 3;
const int d1 = 2;

//extra stuff
int val = 0;
const uint8_t output = OUTPUT;
const uint8_t input  = INPUT;
const uint8_t high = HIGH;
const uint8_t low  = LOW;

void setup() {
  setupArdumoto();
}

void loop() {

}

//motor functions for moving up and down
void up(){
  driveArdumoto(motor1, f, 255);
}
void up(int s){
  driveArdumoto(motor1, f, s);
}
void down(){
  driveArdumoto(motor1, r, 255);
}
void down(int s){
  driveArdumoto(motor1, r, s);
}
void elevate(int s, int d){
  driveArdumoto(motor1, d, s);
}

void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == motor1)
  {
    digitalWrite(d1, dir);
    analogWrite(sc1, spd);
  }
  else{

  }
}
void stopped()
{
  driveArdumoto(motor1, 0, 0);
}
void setupArdumoto()
{
  pinMode(sc1, output);
  pinMode(d1, output);

  digitalWrite(sc1, low);
  digitalWrite(d1, low);
}
