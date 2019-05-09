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

int drink1[3] = {2000, 5000, 10000};
int drink2[3] = {7000, 4000, 9000};
int drink3[3] = {2000, 5000, 3000};
void loop()
{
  if (EEBlue.available() > 0) // Send data only when you receive data:
  {
    data = EEBlue.read();      //Read the incoming data and store it into variable data
    input = EEBlue.readString();
    EEBlue.print(data);        //Print Value inside data in Serial monitor
    EEBlue.print("\n");        //New line
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

    }
    if (data == '3') {          //Checks whether value of data is equal to 1

    }
    
  }

}
