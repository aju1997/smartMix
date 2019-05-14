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
				PD_State = idle;
			}
			else {
				PD_State = pumpOn;
			}
			break;
		case pumpOn:
			PD_State = pour;
			break;
		case p1:
			PD_State = clear1;
			break;
		case clear1:
			PD_State = p2;
			break;
		case p2:
			PD_State = clear2;
			break;
		case clear2:
			PD_State = p3;
			break;
		case p3:
			PD_State = clear3;
			break;
		case clear3:
			PD_State = pumpOff;
			break;
		case pumpOff:
			PD_State = idle;
			break;
	} // end transitions
	switch (PD_States) { // actions
		case idle:
			break;
		case pumpOn:
			digitalWrite(13, HIGH);
			break;
		case pour:
			++cnt;
			break;
		case clearTubes:
			++cnt;
			break;
		case pumpOff:
			digitalWrite(13, LOW);
			break;
		default:
			break;
	} // end actions
}
