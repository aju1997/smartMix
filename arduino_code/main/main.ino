#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char data = 0;     //Variable for storing received data
String input = "";

void setup()
{         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(13, OUTPUT); // PUMP
  pinMode(12, OUTPUT); // Valve 1 uses air to push out remaining water
  pinMode(10, OUTPUT);  // Valve 2 Drink 1
  pinMode(7, OUTPUT); // Valve 3 Drink 2
  pinMode(11, OUTPUT); // Valve 4 Drink 3
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("smartMix");

}

// global
int requestMade = 1;
// state machines
enum PD_States {idle, openValve, waitValve, nextValve} PD_State;
void Tick_PourDrink();

// preset drinks
int drink1[3] = {1, 2, 3};
int drink2[3] = {7000, 4000, 9000};
int drink3[3] = {2000, 5000, 3000};
int pourTimes[3][3] = {*drink1, *drink2, *drink3};
void loop()
{
  Tick_PourDrink();
}

void Tick_PourDrink() {
    /* time to pour 1oz:
     * drink1, drink3, drink3: 3350, 3300, 3450
     */
	static int cnt = 0;
	static int drindex = 0; 
	
	switch (PD_State) { // transitions
		case idle:
            if (requestMade < 0) {
                PD_State = openValve;
                // pump on
                digitalWrite(13,LOW);
                lcd.print("Pump On");
            }
            else {
                PD_State = idle;
            }
            break;
        case openValve:
            PD_State = waitValve;
            break;
        case waitValve:
            if (cnt < pourTimes[requestMade][drindex]){
                PD_State = waitValve;
            }
            else {
                PD_State = nextValve;
            }
            break;
        case nextValve:
            if (drindex < 3) {
                PD_State = openValve;
            }
            else {
                PD_State = idle;
                // pump off
                requestMade = -1;
                digitalWrite(13,HIGH);
            }
            break;
        default:
            PD_State = idle;
            break;
	} // end transitions
	switch (PD_State) { // actions
		case idle:
            break;
        case openValve:
            if (drindex == 0) {
                // open valve 1
                digitalWrite(12,LOW);
                lcd.print("Valve 1 Open");
            }
            else if (drindex == 1) {
                // open valve 2
                digitalWrite(10,LOW);
                lcd.print("Valve 2 Open");
            }
            else if (drindex == 2) {
                // open valve 3
                digitalWrite(11,LOW);
                lcd.print("Valve 3 Open");
            }
            break;
        case waitValve:
            ++cnt;
            break;
        case nextValve:
            // close prev valve, go to next drink valve index
            if (drindex == 0) {
                // open valve 1
                digitalWrite(10,HIGH);
            }
            else if (drindex == 1) {
                // open valve 2
                digitalWrite(9,HIGH);
            }
            else if (drindex == 3) {
                // open valve 3
                digitalWrite(11,HIGH);
            }
            ++drindex;
            break;
		default:
			break;
	} // end actions
}
