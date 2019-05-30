#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void mainMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select    ");
  lcd.setCursor(0, 1);
  lcd.print("Create    ");
}

void chooseMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Presets");
  lcd.setCursor(0, 1);
  lcd.print("Customs");
}

void createMenu(int drink, char amount) {
  //drink += '0';
  amount += '0';
  lcd.setCursor(0, 0);
  // prints drink# currently being edited
  lcd.print("drink");
  lcd.print(drink);
  lcd.print("         "); // clear the cursor "*"
  lcd.setCursor(0, 1);
  lcd.print("ounces: ");
  lcd.print(amount);
  lcd.print("         "); // clear the cursor "*"
}

void pourStoreMenu() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Pour");
	lcd.setCursor(0, 1);
	lcd.print("Store");
}

void confirmDrinkMenu() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Confirm? Yes");
	lcd.setCursor(9, 1);
	lcd.print("No");
}

void storeConfirmMenu() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Confirm? Yes");
	lcd.setCursor(9, 1);
	lcd.print("No");
}

void storeDrinkYesMenu() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Your drink has");
	lcd.setCursor(0, 1);
	lcd.print("been stored!");
}

void pouringDrinkYesMenu() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Your drink is");
	lcd.setCursor(0, 1);
	lcd.print("pouring!");
}