
char reading;
void setup()
{//motor1
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  //motor2
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);

   Serial.begin(9600);
}
void loop()
{
  if (Serial.available())
  reading=Serial.read();
  Serial.println(reading);
  {switch(reading){
    case 'F':
    Forward();
    break; 
    case 'B':
    Back();
    break;
    case 'R':  
    Right();
    break;
    case 'L':  
    Left();
    break;
    default:
    Stop();
    break;
    }
  }}
  
void Forward(){
 digitalWrite(7,HIGH);
 digitalWrite(6,LOW);
 digitalWrite(12,HIGH);
 digitalWrite(13,LOW);}

 void Back(){
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);}
  
  void Right(){
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH); 
    digitalWrite(13,HIGH);
    digitalWrite(12,LOW);}

    void Left(){
        digitalWrite(6,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,HIGH);
        }
        void Stop(){
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
        digitalWrite(13,LOW);
        digitalWrite(12,LOW);}



