
#include <Servo.h>

Servo m1;  // create servo object to control a servo
char reading;
int angle=90;
void setup() {
m1.attach(3);
 Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
  reading=Serial.read();}
  Serial.println(angle);
  switch(reading){
    case 'F':
    Move(1,0,1,0);
    break;
    case 'B':
    Move(0,1,0,1);
    break; 
    case 'l':

    Move(1,0,0,1);    
    break;
    case 'r':
    
    Move(0,1,1,0);
    break; 
    }
   // delay(100);
}
void Move(int a,int b,int c,int d){
 //motor1
   digitalWrite(2,a);
    digitalWrite(3,b);
 //motor2
 digitalWrite(4,c);
     digitalWrite(5,d);}
