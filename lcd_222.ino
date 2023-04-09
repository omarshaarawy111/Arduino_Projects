#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);  
void setup() {
lcd.begin(16,2);
  // put your setup code here, to run once:

}

void loop() {
 
  lcd.clear();
  for(int i=0;i<16;i++){
  lcd.setCursor(i,0);
  lcd.print ("Paula Nashat");
 
  delay(500);
  lcd.clear();}
   for(int i=0;i<16;i++){
  lcd.setCursor(i,1);
  lcd.print ("Paula Nashat");
 
  delay(500);
  lcd.clear();}
 
}  // put your main code here, to run repeatedly:


