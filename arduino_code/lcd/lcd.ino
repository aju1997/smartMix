#include "Menus.h"


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(6,INPUT);
}
#define NONE 0
#define UP 1
#define DWN 2
// gets input from joystick (analog) and button (pin)
int getInput();
// sets position of cursor using joystick input
enum CS_States {none, up, down} CS_State;
void Tick_Joystick();
// navigates menu options
enum M_States {M_init, main, select, create, presets, customs} M_State;
void Tick_Menu();

char cursorPos = 0;
char buttonPress = 0;
void loop() {
    buttonPress = digitalRead(6);
    delay(1);
    Tick_Menu();
    Tick_Joystick();
}

void Tick_Menu() {
  // transitions
  switch (M_State) {
    case M_init:
      M_State = main;
      mainMenu();
      break;
    case main:
      if (buttonPress && cursorPos) {
        M_State = create;
      }
      else if (buttonPress && !cursorPos)  {
        M_State = select;
      }
      else {
        M_State = main;
      }
      break;
    case create:
      break;
    default:
      M_State = M_init;
      break;
  }
  // actions
  switch (M_State) {
    case main:
      break;
    case select:
      selectMenu();
      break;
    case create:
      createMenu(1);
      break;
    default:
      break;
  }
}


int getInput() {
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
void Tick_Joystick() {
  // transitions
  switch (CS_State) {
    case none:
      if (getInput() == UP) {
        CS_State = up;
      }
      else if (getInput() == DWN) {
        CS_State = down;
      }
      else {
        CS_State = none;
      }
      break;
    case up:
      CS_State = none;
      break;
    case down:
      CS_State = none;
      break;
    default:
      CS_State = none;
      break;
      
  }
  // actions
  switch (CS_State) {
    case up:
      lcd.setCursor(13,0);
      lcd.print("*");
      lcd.setCursor(13,1);
      lcd.print(" ");
      cursorPos = 0;
      break;
    case down:
      lcd.setCursor(13,0);
      lcd.print(" ");
      lcd.setCursor(13,1);
      lcd.print("*");
      cursorPos = 1;
      break;
    default:
      break;
  }
}
