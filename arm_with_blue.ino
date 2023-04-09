
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
    angle+=1;
    break;
    case 'B':
    angle-=1;
    break; 
    }
   // delay(100);
    if(angle>180)angle=180;
    else if(angle<0){angle=0;}
m1.write(angle);
}
