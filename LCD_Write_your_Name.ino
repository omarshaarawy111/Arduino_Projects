#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
void setup() {
  lcd.begin(16,2);
 lcd.clear();
lcd.setCursor(2,0);
lcd.print("Paula Nashat");
lcd.setCursor(3,1);
lcd.print("01205624000");
}

void loop() {
}
