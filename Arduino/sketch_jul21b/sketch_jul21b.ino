

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int switchPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int reply;
void setup() {
  pinMode(switchPin,INPUT);
  lcd.print("hows it going");
  lcd.setCursor(0,1);
  lcd.print("bro??");
}
void loop() {
  switchState = digitalRead(switchPin);
  if (switchState !=prevSwitchState) {
    if (switchState == LOW) {
      reply = random(4);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd. print("ball says:");
      lcd.setCursor(0, 1);
      switch(reply){
        case 0:
        lcd.print("fa shooooo");
        break;
        case 1:
        lcd.print("Most Likely");
        break;
        case 2:
        lcd.print("No....Loser");
        break;
        case 3:
        lcd.print("Totally Bro");
        break;
        
      }
    }
  }
  prevSwitchState = switchState;
}
