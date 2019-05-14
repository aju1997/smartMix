#include <SoftwareSerial.h>
char data = 0;     //Variable for storing received data
String input = "";
SoftwareSerial EEBlue(3, 4);
void setup()
{         //Sets the data rate in bits per second (baud) for serial data transmission
  EEBlue.begin(9600);
  pinMode(13, OUTPUT); // PUMP
  pinMode(12, OUTPUT); // Valve 1 uses air to push out remaining water
  pinMode(10, OUTPUT);  // Valve 2 Drink 1
  pinMode(7, OUTPUT); // Valve 3 Drink 2
  pinMode(11, OUTPUT); // Valve 4 Drink 3

}

// global
int requestMade = -1;
// state machines
enum PD_States {idle, pumpOn, p1, clear1, p2, clear2, p3, clear3, pumpOff} PD_State
void Tick_PourDrink();

// preset drinks
int drink1[3] = {2000, 5000, 10000};
int drink2[3] = {7000, 4000, 9000};
int drink3[3] = {2000, 5000, 3000};
int pourTimes[3][3] = {drink1, drink2, drink3}
void loop()
{
  if (EEBlue.available() > 0) // Send data only when you receive data:
  {
    data = EEBlue.read();      //Read the incoming data and store it into variable data
    input = EEBlue.readString();
    EEBlue.print(data);        //Print Value inside data in Serial monitor
    EEBlue.print("\n");        //New line
    requestMade = data - '0';
    if (data == '1' || input == "turn on") {          //Checks whether value of data is equal to 1
      digitalWrite(13, HIGH);
      digitalWrite(7, HIGH);
      delay(5000); // dispense
      digitalWrite(7, LOW);
      digitalWrite(12, HIGH);
      delay(5000); // clear water
      digitalWrite(12, LOW);
      digitalWrite(10, HIGH);
      delay(7000); // dispense 
      digitalWrite(10, LOW);
      digitalWrite(12, HIGH);
      delay(5000); // clear water
      digitalWrite(13, LOW);
      digitalWrite(12, LOW); 
    }
    if (data == '2') {          //Checks whether value of data is equal to 1
      digitalWrite(13, HIGH);
      digitalWrite(7, HIGH);
      delay(6000); // dispense
      digitalWrite(7, LOW);
      digitalWrite(12, HIGH);
      delay(5000); // clear water
      digitalWrite(12, LOW);
      digitalWrite(10, HIGH);
      delay(7500); // dispense 
      digitalWrite(10, LOW);
      digitalWrite(12, HIGH);
      delay(5000); // clear water
      digitalWrite(13, LOW);
      digitalWrite(12, LOW); 
    }
    if (data == '3') {          //Checks whether value of data is equal to 1
      digitalWrite(13, HIGH);
      digitalWrite(7, HIGH);
      delay(4000); // dispense
      digitalWrite(7, LOW);
      digitalWrite(12, HIGH);
      delay(5000); // clear water
      digitalWrite(12, LOW);
      digitalWrite(10, HIGH);
      delay(8000); // dispense 
      digitalWrite(10, LOW);
      digitalWrite(12, HIGH);
      delay(5000); // clear water
      digitalWrite(13, LOW);
      digitalWrite(12, LOW); 
    }
    
  }

}

void Tick_PourDrink() {
	static int cnt = 0;
	static int drindex = 0; 
	
	switch (PD_State) { // transitions
		case idle:
            if (requestMade < 0) {
                PD_State = openValve;
                // pump on
                digitalWrite(13,HIGH);
            }
            else {
                PD_State = idle;
            }
            break;
        case openValve:
            PD_State = valveWait;
            break;
        case valveWait:
            break;
        case nextValve:
            break;
        default:
            PD_State = idle;
            break;
	} // end transitions
	switch (PD_States) { // actions
		case idle:
            break;
        case openValve:
            if (drindex == 0) {
                // open valve 1
                digitalWrite(7,High);
            }
            else if (drindex == 1) {
                // open valve 2
                digitalWrite(10)
            }
            else if (drindex == 3) {
                // open valve 3
                digitalWrite(12);
            }
            break;
        case valveWait:
            ++cnt;
            break;
        case nextValve:
            ++drindex;
            break;
		default:
			break;
	} // end actions
}
