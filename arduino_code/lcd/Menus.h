#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void mainMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Select ");
  lcd.setCursor(0, 1);
  lcd.print("Create ");
}

void selectMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Presets");
  lcd.setCursor(0, 1);
  lcd.print("Customs");
}

void createMenu(char drink, char amount) {
  drink += '0';
  amount += '0';
  lcd.setCursor(0, 0);
  lcd.print("drink");
  lcd.print(drink);
  lcd.setCursor(0, 1);
  lcd.print("ounces: ");
  lcd.print(amount);
}
