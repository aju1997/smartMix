#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String input = "";
char drink[4];
//char drink = 0;     //Variable for storing received data
SoftwareSerial EEBlue(3, 4);
void setup()
{ //Sets the drink rate in bits per second (baud) for serial data transmission
  //  lcd.begin(6, 2);
  //  lcd.print("sma");
  EEBlue.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT); // PUMP
  pinMode(12, OUTPUT); // Valve 1 uses air to push out remaining water
  pinMode(11, OUTPUT);  // Valve 2 Drink 1
  pinMode(10, OUTPUT); // Valve 3 Drink 2
  pinMode(9, OUTPUT); // Valve 4 Drink 3
  digitalWrite(13, HIGH); //pump
  digitalWrite(12, HIGH); //air valve
  digitalWrite(11, HIGH); //left(first) valve
  digitalWrite(10, HIGH); //middle(second) valve
  digitalWrite(9, HIGH);  // right(third) valve
}
// preset drinks
int drink1[3] = {2000, 5000, 10000};
int drink2[3] = {7000, 4000, 9000};
int drink3[3] = {2000, 5000, 3000};
int first = 0;
int second = 0;
int third = 0;

// State Machines
enum PD_States {PD_idle, PD_first, PD_second, PD_third, PD_prime, PD_dispense, PD_air} PD_State;
void Tick_PourDrink();

// main loop
void loop()
{
  if (EEBlue.available() > 0) // Send drink only when you receive data:
  {
    input = EEBlue.readString(); //Read the incoming drink and store it into variable data
    
    input.toCharArray(drink,4);
    
    // grab input
    first = drink[0] - '0';
    second = drink[1] - '0';
    third = drink[2] - '0';

    // use input
    Tick_PourDrink();

    // clear input
    drink[0] = '0';
    drink[1] = '0';
    drink[2] = '0';
    drink[3] = '0';
  }
}

void Tick_PourDrink() {
    static int cnt = 0;
    static int drindex = 0;

    // transitions
    switch (PD_State) {
        case PD_idle:
            if (first || second || third) {
                PD_State = PD_first;
            }
            else {
                PD_State = PD_idle;
            }
            break;
        case PD_first:
            if (first) {
                digitalWrite(11, LOW); // first valve open
                digitalWrite(13, LOW); // pump on
                drindex = 0;
                PD_State = PD_prime; // prime, dispense, clear tubes
            }
            else {
                PD_State = PD_second;
            }
            break;
        case PD_second:
            if (second) {
                digitalWrite(10, LOW); // second valve open
                digitalWrite(13, LOW); // pump on
                drindex = 1;
                PD_State = PD_prime; // prime, dispense, clear tubes
            }
            else {
                PD_State = PD_third;
            }
            break;
        case PD_third:
            if (third) {
                digitalWrite(9, LOW);  // third valve open
                digitalWrite(13, LOW); // pump on
                drindex = 2;
                PD_State = PD_prime; // prime, dispense, clear tubes
            }
            else {
                PD_State = PD_idle;
            }
            break;
        case PD_prime:
            if (cnt < 2000) {
                PD_State = PD_prime;
            }
            else {
                PD_State = PD_dispense;
                cnt = 0;
            }
            break;
        case PD_dispense:
            if (cnt < 1850*drink[drindex]) {
                PD_State = PD_dispense;
            }
            else {
                PD_State = PD_air;
                // close all valves
                digitalWrite(11,HIGH);
                digitalWrite(10,HIGH);
                digitalWrite(9,HIGH);
                // open air valve
                digitalWrite(12, LOW);
                // reset counter
                cnt = 0;
            }
            break;
        case PD_air:
            if (cnt < 5000) {
                PD_State = PD_air;
            }
            else {
                cnt = 0;

                digitalWrite(13, HIGH); // turn off pump
                digitalWrite(12, HIGH); // close air valve
                PD_State = (second) ? PD_second : PD_third;
            }
            break;
        default:
            PD_State = PD_idle;
            break;
    }
    // actions
    switch (PD_State) {
        case PD_idle:
            // be idle
            break;
        case PD_first:
            drindex = 0;
            break;
        case PD_second:
            drindex = 1;
            break;
        case PD_third:
            drindex = 2;
            break;
        case PD_prime:
            ++cnt;
            break;
        case PD_dispense:
            ++cnt;
            break;
        case PD_air:
            ++cnt;
            break;
        default:
            // do nothing
            break;
    }
}
