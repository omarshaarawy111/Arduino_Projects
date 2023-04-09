int reading;
void setup() {
Serial.begin(9600);
}

void loop() {
  reading=analogRead(A0);
  Serial.println(reading);
  delay(50);
}
