#include "Menus.h"


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(6,INPUT);
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
enum M_States {M_init, main, select, create, presets, customs} M_State;
void Tick_Menu();

// increment and decrement a value with joystick (used for menu navigation)
enum ID_States {idle, increment, waitRelease, decrement} ID_State;
void Tick_IncDec();
char value = 0;

char cursorPos = 0;
char buttonPress = 0;
void loop() {
    buttonPress = digitalRead(6);

    delay(1);
    Tick_Menu();
    Tick_IncDec();
    Tick_CursorPos();
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
  static char drindex = 0;
  // transitions
  switch (M_State) {
    case M_init:
      M_State = main;
      mainMenu();
      break;
    case main:
      // uses input from Tick_CursorPos
      if (buttonPress && cursorPos) {
        M_State = create;
        createMenu(1, 0);
      }
      else if (buttonPress && !cursorPos)  {
        M_State = select;
        selectMenu();
      }
      else {
        M_State = main;
      }
      break;
    case create:
      if (drindex < 3) {
          M_State = create;
      }
      else {
          M_State = main;
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
      lcd.setCursor(13,0);
      if (!cursorPos)
        lcd.print("*");
      else
        lcd.print(" ");
      lcd.setCursor(13,1);
      if (!cursorPos)
        lcd.print(" ");
      else
        lcd.print("*");
      break;
    case select:
      break;
    case create:
      if (buttonPress) {
          // FIXME: button press captured too fast,
          //        increment is buggy (make SM for button?)
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
      createMenu(0, value);
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
