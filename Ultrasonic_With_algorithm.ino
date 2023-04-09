int echoPin = 13;
int trigPin = 12;
long duration;
float dist;
void setup() {
  // put your setup code here, to run once:
 pinMode(trigPin, OUTPUT);
 Serial.begin(9600);
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
  distance();
  delay(100);
}
