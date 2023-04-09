#include <Keypad.h>
#define segA A5//connecting segment A to PIN2
#define segB A4// connecting segment B to PIN3
#define segC 2// connecting segment C to PIN4
#define segD 3// connecting segment D to PIN5
#define segE 4// connecting segment E to PIN6
#define segF 5// connecting segment F to PIN7
#define segG 6// connecting segment G to PIN8
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
int COUNT=0;//count integer for 0-9 increment
int button1;
int button2;
int COUNT2=COUNT/10;
int digit=0;
int digit2=0;
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {

{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {7,8,9,10}; 
byte colPins[COLS] = {11,12,13,A0}; 
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 char customKey ;
void setup(){
pinMode(A0,INPUT);
pinMode(A4,OUTPUT);
pinMode(A5,OUTPUT);
Serial.begin(9600);
  for(int i=2;i<7;i++){
  pinMode(i,OUTPUT);}
  Serial.begin(9600);
}
  void Segment(){
  switch (customKey)
 
               {case'0'://when count value is zero show”0” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, LOW);
                break;
 
                case '1':// when count value is 1 show”1” on disp
                digitalWrite(segA, LOW);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, LOW);
                digitalWrite(segE, LOW);
                digitalWrite(segF, LOW);
                digitalWrite(segG, LOW);
                break;
 
                case '2':// when count value is 2 show”2” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, LOW);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, LOW);
                digitalWrite(segG, HIGH);
                break;
 
                case '3':// when count value is 3 show”3” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, LOW);
                digitalWrite(segF, LOW);
                digitalWrite(segG, HIGH);
                break;
 
                case '4':// when count value is 4 show”4” on disp
                digitalWrite(segA, LOW);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, LOW);
                digitalWrite(segE, LOW);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;
 
                case '5':// when count value is 5 show”5” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, LOW);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, LOW);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;
 
                case '6':// when count value is 6 show”6” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, LOW);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;
 
                case '7':// when count value is 7 show”7” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, LOW);
                digitalWrite(segE, LOW);
                digitalWrite(segF, LOW);
                digitalWrite(segG, LOW);
                break;
 
                case '8':// when count value is 8 show”8” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, HIGH);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;
 
                case '9':// when count value is 9 show”9” on disp
                digitalWrite(segA, HIGH);
                digitalWrite(segB, HIGH);
                digitalWrite(segC, HIGH);
                digitalWrite(segD, HIGH);
                digitalWrite(segE, LOW);
                digitalWrite(segF, HIGH);
                digitalWrite(segG, HIGH);
                break;
 
                break;}
                }
          

void loop(){
customKey = customKeypad.getKey();
  Segment();
 if (customKey){
    Serial.println(customKey);

  }
}
