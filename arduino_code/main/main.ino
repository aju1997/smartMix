#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char data = 0;     //Variable for storing received data
String input = "";
SoftwareSerial EEBlue(3, 4);
void setup()
{ //Sets the data rate in bits per second (baud) for serial data transmission
  //  lcd.begin(6, 2);
  //  lcd.print("sma");
  EEBlue.begin(9600);
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
    // 111
     digitalWrite(11, HIGH); //left(first) valve
  digitalWrite(10, HIGH); //middle(second) valve
  digitalWrite(9, HIGH);  // right(third) valve
    if (data[0] > 0 && data[1] > 0 && data[2] > 0) { // output from all 3 drinks
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay((data[0] - '0')*2450); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); //air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(10, LOW); //middle valve
      delay((data[1] - '0')*2700); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(9, LOW); //right valve
      delay((data[2] - '0')*3000); // dispense
      digitalWrite(9, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (data[0] > 0 && data[1] == 0 && data[2] > 0) { //output from #1 and #3 drink
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay((data[0] - '0')*3350); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); //air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(9, LOW); //right valve
      delay((data[2] - '0')*3450); // dispense
      digitalWrite(9, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (data[0] > 0 && data[1] > 0 && data[2] == 0) { //output from #1 and #2 drink
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay((data[0] - '0')*3350); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); //air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(10, LOW); //middle valve
      delay((data[1] - '0')*3300); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (data[0] == 0 && data[1] > 0 && data[2] > 0) { //output from #2 and #3 drink
      digitalWrite(13, LOW);//pump
      digitalWrite(10, LOW); //middle valve
      delay((data[1] - '0')*3300); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(9, LOW); //right valve
      delay((data[2] - '0')*3450); // dispense
      digitalWrite(9, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (data[0] > 0 && data[1] == 0 && data[2] == 0) { //output from #1 drink
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay((data[0] - '0')*3350); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (data[0] == 0 && data[1] > 0 && data[2] == 0) { //output from #2 drink
      digitalWrite(13, LOW);//pump
      digitalWrite(10, LOW); //middle valve
      delay((data[1] - '0')*3300); // dispense
      digitalWrite(10, HIGH);
      
      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (data[0] == 0 && data[1] == 0 && data[2] > 0) { //output from #3 drink
      digitalWrite(13, LOW);//pump
      digitalWrite(9, LOW); //right valve
      delay((data[2] - '0')*3450); // dispense
      digitalWrite(9, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    
//    if (data == '0') { 
//      digitalWrite(13, LOW);//pump
//      digitalWrite(10, LOW);//left valve
//      delay(4900); // dispense
//      digitalWrite(10, HIGH);
//
//      digitalWrite(12, LOW); //air valve
//      delay(5000); // clear water
//      digitalWrite(12, HIGH);
//
//      digitalWrite(9, LOW); //middle valve
//      delay(5400); // dispense
//      digitalWrite(9, HIGH);
//
//      digitalWrite(12, LOW); // air valve
//      delay(5000); // clear water
//      digitalWrite(12, HIGH);
//
////      digitalWrite(9, LOW); //right valve
////      delay(6000); // dispense
////      digitalWrite(9, HIGH);
////
////      digitalWrite(12, LOW); // air valve
////      delay(5000); // clear water
//      digitalWrite(13, HIGH);
////      digitalWrite(12, HIGH);
//    }
//    if (data == '1' || input == "turn on") {          //Checks whether value of data is equal to 1
//
//      digitalWrite(13, LOW);
//      digitalWrite(11, LOW);
//      delay(3350);
//      digitalWrite(11, HIGH);
//      digitalWrite(12, LOW);
//      delay(5000);
//      digitalWrite(13, HIGH);
//      digitalWrite(12, HIGH);
//    }
//    if (data == '2') {          //Checks whether value of data is equal to 1
//      //      digitalWrite(13, HIGH);
//      //      digitalWrite(7, HIGH);
//      //      delay(6000); // dispense
//      //      digitalWrite(7, LOW);
//      //      digitalWrite(12, HIGH);
//      //      delay(5000); // clear water
//      //      digitalWrite(12, LOW);
//      //      digitalWrite(10, HIGH);
//      //      delay(7500); // dispense
//      //      digitalWrite(10, LOW);
//      //      digitalWrite(12, HIGH);
//      //      delay(5000); // clear water
//      //      digitalWrite(13, LOW);
//      //      digitalWrite(12, LOW);
//      digitalWrite(13, LOW);
//      digitalWrite(10, LOW);
//      delay(3300);
//      digitalWrite(10, HIGH);
//      digitalWrite(12, LOW);
//      delay(5000);
//      digitalWrite(13, HIGH);
//      digitalWrite(12, HIGH);
//    }
//    if (data == '3') {          //Checks whether value of data is equal to 1
//      //      digitalWrite(13, HIGH);
//      //      digitalWrite(7, HIGH);
//      //      delay(4000); // dispense
//      //      digitalWrite(7, LOW);
//      //      digitalWrite(12, HIGH);
//      //      delay(5000); // clear water
//      //      digitalWrite(12, LOW);
//      //      digitalWrite(10, HIGH);
//      //      delay(8000); // dispense
//      //      digitalWrite(10, LOW);
//      //      digitalWrite(12, HIGH);
//      //      delay(5000); // clear water
//      //      digitalWrite(13, LOW);
//      //      digitalWrite(12, LOW);
//      digitalWrite(13, LOW);
//      digitalWrite(9, LOW);
//      delay(3450);
//      digitalWrite(9, HIGH);
//      digitalWrite(12, LOW);
//      delay(5000);
//      digitalWrite(13, HIGH);
//      digitalWrite(12, HIGH);
//
//    }

  }

}
