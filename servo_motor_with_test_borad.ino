
#include <Servo.h>

Servo m1;  // create servo object to control a servo
Servo m2;  // create servo object to control a servo
Servo m3; 
int angle1,angle2,angle3;    // variable to store the servo position

void setup() {
  m1.attach(3);  // attaches the servo on pin 9 to the servo object
  m2.attach(5);
  m3.attach(6);}

void loop() {
  angle1=analogRead(0);
  angle1=map(angle1,0,1023,0,180);
  m1.write(angle1);
  
  angle2=analogRead(1);
  angle2=map(angle2,0,1023,0,180);
  m2.write(angle2);
  
  angle3=analogRead(2);
  angle3=map(angle3,0,1023,0,180);
  m3.write(angle3);
  }

