#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int echoPin = 13;
int trigPin = 12;
long duration;
float dist;
void setup() {
  lcd.begin(16,2);
 lcd.clear();
  pinMode(trigPin, OUTPUT);

}

void distance(){ 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin,HIGH);
  dist = (duration/2)/29.1;
  Serial.print("Distance=  ");
  Serial.println(dist);
}

void loop() {
   lcd.clear();
  distance();
  lcd.setCursor(2,0);
lcd.print("distance");
lcd.setCursor(3,1);
lcd.print(dist);
delay(100);

}
