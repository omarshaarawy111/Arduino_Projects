int button= 8;
int RedLed= 5 ;
int yellowLed=6 ;
int greenLed=7;
int count =0;

int reading;
void setup() {
  pinMode(button,INPUT);
  pinMode(RedLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  digitalWrite(RedLed,LOW);
  digitalWrite(yellowLed,LOW);
  digitalWrite(greenLed,LOW);

}

void loop() {
reading= digitalRead(button);
if(reading==1){
  delay(50);
  reading= digitalRead(button);
  if(reading==0){
count++;}
  }

switch (count){
case 1:
  digitalWrite(RedLed,HIGH);
  digitalWrite(yellowLed,LOW);
  digitalWrite(greenLed,LOW);

break;
case 2:
  digitalWrite(RedLed,LOW);
  digitalWrite(yellowLed,HIGH);
  digitalWrite(greenLed,LOW);

break;
case 3:
  digitalWrite(RedLed,LOW);
  digitalWrite(yellowLed,LOW);
  digitalWrite(greenLed,HIGH);

break;
default:
 digitalWrite(RedLed,LOW);
  digitalWrite(yellowLed,LOW);
  digitalWrite(greenLed,LOW);
    count=0;
break;
}
}
