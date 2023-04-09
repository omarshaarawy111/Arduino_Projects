

const int trigPin = 8;
const int trigPin1 = 13;
const int echoPin = 9;
const int echoPin1 = 12;
const int buzzer = 5;
const int motor = 3;
const int maxout = 200;

// defines variables

long duration;
long duration1;
int distance;
int distance1;


void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(motor, OUTPUT);
Serial.begin(9600);
}


void loop() {

  duration = pulseIn(echoPin, HIGH);
  duration1 = pulseIn(echoPin1, HIGH);
  distance = (duration/2)/29.1;
  distance1 = (duration1/2)/29.1;  
  
 if (distance >= 100 || distance1 >= 100) 
 {
   
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
   digitalWrite(motor,HIGH);
   delay(200);
 }
   
if (distance < 100 || distance1 <= 100) 
{
   digitalWrite(motor,LOW);
   digitalWrite(buzzer,HIGH);
   delay(200);
}

 Serial.print("Distance1: ");
 Serial.println(distance); 
 Serial.print("Distance2: ");
 Serial.println(distance1); 
 delay(500);}
