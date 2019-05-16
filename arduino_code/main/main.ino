#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String input = "";
char data[4];
//char data = 0;     //Variable for storing received data
SoftwareSerial EEBlue(3, 4);
void setup()
{ //Sets the data rate in bits per second (baud) for serial data transmission
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

int drink1[3] = {2000, 5000, 10000};
int drink2[3] = {7000, 4000, 9000};
int drink3[3] = {2000, 5000, 3000};
int first = 0;
int second = 0;
int third = 0;
void loop()
{
  if (EEBlue.available() > 0) // Send data only when you receive data:
  {
    input = EEBlue.readString(); //Read the incoming data and store it into variable data
    
    input.toCharArray(data,4);
//    Serial.print(input);
//    Serial.print(data);
//    input = EEBlue.readString();
//    Serial.print(data);
    
    first = data[0] - '0';
    second = data[1] - '0';
    third = data[2] - '0';
//    Serial.print(data[0]);
//    Serial.print(data[1]);
//    Serial.print(data[2]);
//    Serial.print("data");
//    Serial.print(first);
//    Serial.print(second);
//    Serial.print(third);
//    Serial.print("end");
    if (first > 0 && second > 0 && third > 0) { // output from all 3 drinks
      Serial.print("Drink 1, 2, 3\n");
      //change
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay(1000);
      delay(first*1800); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); //air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(10, LOW); //middle valve
      delay(second*1400); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(9, LOW); //right valve
      delay(third*1400); // dispense
      digitalWrite(9, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (first > 0 && second == 0 && third > 0) { //output from #1 and #3 drink
      Serial.print("Drink 1, 3\n");
      
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay(1000);
      delay(first*1800); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); //air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(9, LOW); //right valve
      delay(third*1400); // dispense
      digitalWrite(9, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (first > 0 && second > 0 && third == 0) { //output from #1 and #2 drink
      Serial.print("Drink 1, 2\n");
      
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay(1000);
      delay(first*1800); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); //air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(10, LOW); //middle valve
      delay(second*1400); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (first == 0 && second > 0 && third > 0) { //output from #2 and #3 drink
      Serial.print("Drink 2, 3\n");
      
      digitalWrite(13, LOW);//pump
      digitalWrite(10, LOW); //middle valve
      delay(1000);
      delay(second*1800); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(12, HIGH);

      digitalWrite(9, LOW); //right valve
      delay(third*1400); // dispense
      digitalWrite(9, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (first > 0 && second == 0 && third == 0) { //output from #1 drink
      Serial.print("Drink 1\n");
      
      digitalWrite(13, LOW);//pump
      digitalWrite(11, LOW);//left valve
      delay(1500);
      delay(first*1900); // dispense
      digitalWrite(10, HIGH);

      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (first == 0 && second > 0 && third == 0) { //output from #2 drink
      Serial.print("Drink 2\n");
      
      digitalWrite(13, LOW);//pump
      digitalWrite(10, LOW); //middle valve
      delay(1500);
      delay(second*1900); // dispense
      digitalWrite(10, HIGH);
      
      digitalWrite(12, LOW); // air valve
      delay(5000); // clear water
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if (first == 0 && second == 0 && third > 0) { //output from #3 drink
      Serial.print("Drink 3\n");
      
      digitalWrite(13, LOW);//pump
      digitalWrite(9, LOW); //right valve
      delay(1500);
      delay(third*1900); // dispense
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
