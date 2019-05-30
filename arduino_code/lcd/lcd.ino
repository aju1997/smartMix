#include "Menus.h"

byte arrowCursor[8] = {
  B00010,
  B00110,
  B01110,
  B11110,
  B01110,
  B00110,
  B00010,
  B00000
};

void setup() {
  // put your setup code here, to run once:
  lcd.createChar(0, arrowCursor);
  lcd.begin(16, 2);
  lcd.write(byte(0));
  pinMode(6,INPUT);
  Serial.begin(9600);
}

#define NONE 0
#define UP 1
#define DWN 2

// gets y axis input from joystick (analog)
int getYinput();

// sets position of cursor using joystick input
enum CP_States {none, up, down} CP_State;
void Tick_CursorPos();

// navigates menu options
enum M_States {M_init, main, choose, create, presets, customs, pourStore, confirmDrink, store, storeConfirm, yesDrink} M_State;
void Tick_Menu();

// increment and decrement a value with joystick (used for menu navigation)
enum ID_States {idle, increment, waitRelease, decrement} ID_State;
void Tick_IncDec();
int value = 0;
String data = "0";

enum Button_States {low, high, wait} Button_State;
void Tick_Button();

char cursorPos = 0;
char buttonPress = 0;
char buttonHold = 0;

void cursor() {
  lcd.setCursor(13,0);
    if (!cursorPos)
      lcd.write(byte(0));
    else
      lcd.print(" ");
    lcd.setCursor(13,1);
    if (!cursorPos)
      lcd.print(" ");
    else
      lcd.write(byte(0));
}

void loop() {
    buttonPress = digitalRead(6);

    delay(1);
    Tick_Menu();
    Tick_IncDec();
    Tick_CursorPos();
    Tick_Button();
}

/* inputs: gets joystick up/down input position
 * return: the updated value of char value
 * char value is used by Tick_Menu SM when creating drink and to choose drink?
 */
void Tick_IncDec() {
    // transitions
    switch (ID_State) {
        case idle:
            if (getYinput() == UP) {
              ID_State = increment;
            }
            else if (getYinput() == DWN) {
              ID_State = decrement;
            }
            else {
              ID_State = idle;
            }
            break;
        case increment:
            ID_State = waitRelease;
            break;
        case decrement:
            ID_State = waitRelease;
            break;
        case waitRelease:
            if (getYinput()) {
              ID_State = waitRelease;
            }
            else {
              ID_State = idle;
            }
            break;
        default:
            ID_State = idle;
            break;
    }
    // actions
    switch (ID_State) {
      case increment:
        ++value;
        break;
      case decrement:
        --value;
        break;
      default:
        break;
    }
}

/* inputs: either an increment/decrement or select top/bottom
 *         using Tick_IncDec() or Tick_CursorPos respectively
 * return: prints current menu screen from Menus.h (most LCD writing done here)
 */
void Tick_Menu() {
  static int drindex = 0;
  static int storeCounter = 0;
  static int yesDrinkCounter = 0;
  // transitions
  switch (M_State) {
    case M_init:
      M_State = main;
      mainMenu();
      break;
    case main:
      // uses input from Tick_CursorPos
      if (cursorPos && !buttonHold && buttonPress) { //create state
        M_State = create;
        drindex = 0;
        createMenu(drindex, 0);
      }
      else if (!cursorPos && !buttonHold && buttonPress)  { //select state
        M_State = choose;
        chooseMenu();
      }
      else {
        M_State = main;
      }
      break;
    case create:
      if (drindex < 4) { //once 3 drinks are done
          M_State = create;
      }
      else {
          M_State = pourStore;
          pourStoreMenu();
      }
      break;
    case pourStore:
      if (cursorPos && !buttonHold && buttonPress) {
        M_State = storeConfirm;
        storeConfirmMenu();
      }
      else if (!cursorPos && !buttonHold && buttonPress) {
        M_State = confirmDrink;
        confirmDrinkMenu();
      }
      else {
        M_State = pourStore;
      }
      break;
    case confirmDrink:
      if (!cursorPos && !buttonHold && buttonPress) {
        M_State = yesDrink;
        pouringDrinkYesMenu();
      }
      else if (cursorPos && !buttonHold && buttonPress) {
        M_State = main;
        mainMenu();
      }
      else {
        M_State = confirmDrink;
      }
      break;
    case store:
      if (storeCounter < 1500) {
        M_State = store;
      }
      else {
        storeCounter = 0;
        M_State = main;
        mainMenu();
      }
      break;
    case storeConfirm:
      if (!cursorPos && !buttonHold && buttonPress) {
        M_State = store;
        storeDrinkYesMenu();
      }
      else if (cursorPos && !buttonHold && buttonPress) {
        M_State = main;
        mainMenu();
      }
      else {
        M_State = storeConfirm;
      }
      break;
    case yesDrink:
      if (yesDrinkCounter < 2500) {
        M_State = yesDrink;
      }
      else {
        yesDrinkCounter = 0;
        M_State = main;
        mainMenu();
      }
      break;
    default:
      M_State = M_init;
      break;
  }
  // actions
  switch (M_State) {
    case main:
      // print cursor
      cursor();
      break;
    case choose: //still need to do
      break;
    case create:
      if (!buttonHold && buttonPress) {
          ++drindex;
          value = 0;
      }
      // value comes from Tick_IncDec, in this case its requested volume
      if (value >= 9) {
        value = 9;
      }
      else if (value <= 0) {
        value = 0;
      }
      //add if statements to store the value of what the user specified
      
//      if (drindex == 1 && data.length() == 1 && data[0] != value) {
//        data[0] = String(value);
//        Serial.print(data);
//      }
//      if (drindex == 2) {
//        data += String(value);
//      }
//      if (drindex == 3) {
//        data += String(value);
//      }
      //Serial.print(data);
      createMenu(drindex, value);
      break;
    case pourStore:
      cursor();
      break;
    case confirmDrink:
      cursor();
      break;
    case store:
      ++storeCounter;
      break;
    case storeConfirm:
      cursor();
      break;
    case yesDrink:
      ++yesDrinkCounter;
      break;
    default:
      break;
  }
}

/* inputs: none
 * return: immediate joystick position: up, down, or none (center position)
 */
int getYinput() {
  if (analogRead(A1) > 550) {
    return UP;
  }
  else if ( analogRead(A1) < 450) {
    return DWN;
  }
  else {
    return 0;
  }
}
/* inputs: joystick position input
 * return: store the cursor position
 */
void Tick_CursorPos() {
    if (getYinput() == UP) 
        cursorPos = 0;
    else if (getYinput() == DWN)
        cursorPos = 1;
}

void Tick_Button() {
   switch (Button_State) { //Transitions
        case low:
            if (buttonPress) {
              Button_State = high;
            }
            else {
              Button_State = low;
            }
            break;
        case high:
            Button_State = wait;
            break;
        case wait:
            if (buttonPress) {
              Button_State = wait;
            }
            else {
              Button_State = low;
            }
            break;
        default:
            Button_State = low;
            break;
    }
    switch (Button_State) { //Actions
        case low:
            buttonHold = 0; //not holding
            break;
        case high:
            buttonHold = 1; //holding
            break;
        case wait:
            break;
        default:
            break;
    }
}
