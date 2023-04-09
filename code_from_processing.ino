int state;
void setup(){
  pinMode(3,1);
  pinMode(7,1);
  digitalWrite(7,0);
  Serial.begin(9600);
  
}
void loop(){
  if(Serial.available() >0) {
    state=Serial.read();
  }
  analogWrite(3,state);
 
    
   }

