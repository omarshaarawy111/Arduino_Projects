float vout;
float tempC;
void setup(){
  Serial.begin(9600);
}
void loop(){
  vout=analogRead(A0);
  tempC=(vout*500)/1023;
  Serial.print("temperature= ");
  Serial.println(tempC);
  delay(100);
}

