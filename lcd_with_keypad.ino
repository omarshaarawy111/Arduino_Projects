
#include <Keypad.h>
int i=0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columnsg
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {8,9,10,11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {12,13,A0,A1}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   lcd.begin(16,2);
 lcd.clear();
}

void loop() {  char customKey = customKeypad.getKey();
if(customKey){
  lcd.setCursor(i,0);
  lcd.print(customKey);
i++;
if(i>16){
  lcd.clear();
  i=0;}}
}
