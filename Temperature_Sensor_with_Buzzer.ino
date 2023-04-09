#include <LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,9,10,11,12,13); 
int button_state; 
float vout;//volatge output of sensor
float tempC; //temperature vlaue
void setup(){
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("welcome");
delay(500);
lcd.clear();
pinMode(1,OUTPUT);//buzzer
pinMode(2,OUTPUT);//led 1 
pinMode(3,OUTPUT);//led 2
pinMode(4,OUTPUT);//fan
pinMode(5,INPUT);//button 
}
void loop(){
  button_state=digitalRead(5);
  if (button_state==HIGH){
  vout=analogRead(A0);//sensor
  tempC=(vout*500)/1023;//sensitivity
  lcd.setCursor(2,0);//position of temparature word
  lcd.print("temperature= ");
  lcd.setCursor(13,0);//position of temperature value
  lcd.println(tempC);
  if(tempC>50)
  {digitalWrite(2,HIGH);//led 2
   digitalWrite(1,HIGH);//buzzer
   digitalWrite(4,HIGH);//fan
   lcd.setCursor(7,1);
   lcd.print("dangerous");
  }
  else{
   digitalWrite(2,HIGH);
   lcd.setCursor(7,1);
   lcd.print("         ");
  }  
  }
  else {}
}

