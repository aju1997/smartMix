#include <SoftwareSerial.h>

/*
  FOR NOW WORK WILL BE SHOWN AS COMMIT BY SAUL,
  BUT WORK WAS DONE BY Hector and Anderson
  AFTER MILESTONE 1 WILL MAKE SURE COMMITS ARE DONE
  INDIVIDUALLY.
*/
char data = 0;     //Variable for storing received data
String input = "";
SoftwareSerial EEBlue(3, 4);
void setup()
{         //Sets the data rate in bits per second (baud) for serial data transmission
  EEBlue.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT); 
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT); //Sets digital pin 13 as output pin
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
      digitalWrite(12, HIGH);
      delay(drink1[0]);
      digitalWrite(12, LOW);
      digitalWrite(7, HIGH);
      delay(drink1[1]);
      digitalWrite(7, LOW);
      digitalWrite(10, HIGH);
      delay(drink1[2]);
      digitalWrite(10, LOW);
      digitalWrite(13, LOW);
    }
    if (data == '2') {          //Checks whether value of data is equal to 1
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      delay(drink2[0]);
      digitalWrite(12, LOW);
      digitalWrite(7, HIGH);
      delay(drink2[1]);
      digitalWrite(7, LOW);
      digitalWrite(10, HIGH);
      delay(drink2[2]);
      digitalWrite(10, LOW);
      digitalWrite(13, LOW);
    }
    if (data == '3') {          //Checks whether value of data is equal to 1
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      delay(drink3[0]);
      digitalWrite(12, LOW);
      digitalWrite(7, HIGH);
      delay(drink3[1]);
      digitalWrite(7, LOW);
      digitalWrite(10, HIGH);
      delay(drink3[2]);
      digitalWrite(10, LOW);
      digitalWrite(13, LOW);
    }
    
  }

}
