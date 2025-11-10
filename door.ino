//for the door
#include <Servo.h>

//servo object and pin value
Servo servo;
const int SPin = 9;

//sensors pin and values
const int triggerPin = 11;
const int echoPin  = 12;

//diode (lights) we may need; pin value
const int redpin = 3;
const int greenpin = 5;
const int bluepin = 6; 

// extra values may need
float distance = 0;
bool close = false;
const uint8_t output = OUTPUT;
const uint8_t input  = INPUT;
const uint8_t high = HIGH;
const uint8_t low  = LOW;



void setup() {
  Serial.begin(9600);
  serveroSetup();
  sensorsetup();
  diodesetup();

}

void loop() {
  distance = getDistance();
  alert(distance);
  if(close){
    openDoor();
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

//sensor methods
void sensorsetup(){
  pinMode(triggerPin, output);
  pinMode(echoPin, input);
}
float getDistance(){
  float time;
  float calcDistance;

  digitalWrite(triggerPin, high);
  delayMicroseconds(10);
  digitalWrite(triggerPin, low);
  time = pulseIn(triggerPin, low);
  calcDistance = time / 148.0; //calcs a distance in inch
  //calcDistance = time / 58; // calcs a distance in cm

  return calcDistance; //should return a value in inch
}

//diode methods
void diodesetup(){
  pinMode(redpin, output);
  pinMode(greenpin, output);
  pinMode(bluepin, output);
}

void lightup(char s, int v){
  switch(s){
    case 'r':
      analogWrite(redpin, v);
      analogWrite(greenpin, 0);
      analogWrite(bluepin, 0);
      break;

    case 'b':
      analogWrite(redpin, 0);
      analogWrite(greenpin, 0);
      analogWrite(bluepin, v);
      break;

    case 'g':
      analogWrite(redpin, 0);
      analogWrite(greenpin, v);
      analogWrite(bluepin, 0);
      break;
    
    default:
      analogWrite(redpin, 0);
      analogWrite(greenpin, 0);
      analogWrite(bluepin, 0);
      //break;
  }
}
void alert(int d){
  //checks the distance of said object
  //lights up diodes, and opens door.
  if(d <= 10){
    lightup('r', 255);
    close = true;
  }
  else if(d <= 20){
    lightup('g', 255);
    close = false;
  }
  else if(d <= 30){
    lightup('b', 255);
    close = false;
  }
  else{
    lightup('z', 0);
    close = false;
  }
}

//opening the door.
void openDoor(){
    if(close){
      Sangle(0);
      delay(15000); //delay by 15 seconds
      Scenter(); //returns back to 90 degrees 
      //NOTE: talk with group about the door angles

      //door will close after 15 seconds has gone by
    }
}



