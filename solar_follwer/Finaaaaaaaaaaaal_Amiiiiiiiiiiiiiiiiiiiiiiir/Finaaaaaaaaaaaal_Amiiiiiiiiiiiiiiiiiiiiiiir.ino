#include <Servo.h>
Servo horizontal;
Servo vertical;
int val1;
int val2;
int val3;
int val4;
int ava1;
int ava2;
int ava3;
int ava4;
char bluetooth;
int pos=0;
int angle1=0;
int angle2=0;
int posB;
int angleB1;
int AA;
int x;
void setup() {
pinMode(13,OUTPUT);
digitalWrite(13,HIGH);
Serial.begin(9600);
horizontal.attach(9);
vertical.attach(10);
horizontal.write(90);
vertical.write(90);
pinMode(7,INPUT);
}
void motors(){

  if(ava1<ava3){
   horizontal.write(100); 
    }
    if(ava1>ava3){
      
      
   horizontal.write(80); 
   
    }
     if(ava4>ava2){
       pos=pos+10;
       angle1=pos+90;
     
   vertical.write(angle1);
   
    }
    if(ava4<ava2){
      pos=pos-10;
      angle2=90+pos;
    

   vertical.write(angle2); 
  
    }
     if (angle2==10){angle2=0;}
    if(pos>=100)pos=100;
   
    else if (angle1==170){angle1=180;}
  } 
  void motorsWtihBluetooth(){
    if(bluetooth=='F')
    {   AA=AA+2;
       
   vertical.write(AA);}
    if(bluetooth=='B')
    {
           AA=AA-2
           
           ;;
       
     
   vertical.write(AA);}
   if(bluetooth=='L')
    {         
   horizontal.write(85); }
    if(bluetooth=='R')
    {
               
   horizontal.write(95); }
    }

void reading(){
  val1=analogRead(A0);
 val2=analogRead(A1);
 val3=analogRead(A2);
 val4=analogRead(A3);
 ava1=(val1+val2)/2;
 ava2=(val2+val3)/2;
 ava3=(val3+val4)/2;
 ava4=(val1+val4)/2;
 
 Serial.print("avarage1 =  ");
  Serial.print(ava1);
  Serial.print("    ");
 Serial.print("avarage2 =  ");
 Serial.print(ava2);
  Serial.print("  avarage3 =  ");
  Serial.print(ava3);
  Serial.print("    ");
 Serial.print("avarage4 =  ");
 Serial.println(ava4);
  delay(500); 
 
  }
void loop() { 
   if(digitalRead(7)==HIGH){
    reading();
    motors();
    }
    if(digitalRead(7)==LOW){
  if(Serial.available()){
    bluetooth=Serial.read();
    Serial.println(bluetooth);
motorsWtihBluetooth();
  }
  }
}
