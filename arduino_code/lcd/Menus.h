#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void mainMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select    ");
  lcd.setCursor(0, 1);
  lcd.print("Create    ");
}
void selectMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Preset Drinks");
  lcd.setCursor(0, 1);
  lcd.print("Custom Drinks");
}
void choosePresetMenu(int drink, int volumes[3]) {
  lcd.setCursor(0, 0);
  if (drink == 1) {
    lcd.print("    Dongster    ");
  }
  else if (drink == 2) {
    lcd.print("   Hectoroni    ");
  }
  else if (drink == 3) {
    lcd.print("       Aju      ");
  }
  else if (drink == 4) {
    lcd.print("     Salulu     ");
  }
  lcd.setCursor(0, 1);
  lcd.print("volume: ");
  lcd.print(volumes[0]);
  lcd.print(",");
  lcd.print(volumes[1]);
  lcd.print(",");
  lcd.print(volumes[2]);
  lcd.print("  ");
}
void noCustomSaved() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("No drinks");
  lcd.setCursor(0, 1);
  lcd.print("saved yet");
}

void chooseCustomMenu(int drink, int first, int second, int third) {
  lcd.setCursor(0, 0);
  lcd.print("   drink");
  lcd.print(drink);
  lcd.print("        ");
  lcd.setCursor(0, 1);
  lcd.print("volume: ");
  lcd.print(first);
  lcd.print(",");
  lcd.print(second);
  lcd.print(",");
  lcd.print(third);
  lcd.print("     ");
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
