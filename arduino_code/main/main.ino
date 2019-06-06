 #include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String input = "";
char data[4];
int i = 0;
SoftwareSerial EEBlue(3, 4);

void setup()
{ 
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
   data[0] = '0';
   data[1] = '0';
   data[2] = '0';
   data[3] = '0';
  //Slave Receiver
  Wire.begin(4500);                // join i2c bus with address #9
  Wire.onReceive(receiveEvent); // register event
}

int drink1[3] = {2000, 5000, 10000};
int drink2[3] = {7000, 4000, 9000};
int drink3[3] = {2000, 5000, 3000};
int first = 0;
int second = 0;
int third = 0;

void receiveEvent(int abc) {
 
  
  
}


void loop()
{
  //LCD Read
// Wire.requestFrom(8, 6);
 Wire.onReceive(receiveEvent);
  if (Wire.available() > 0) {
    
    i = 0;
    while (i < 3) { // loop through all except last character
    char c = Wire.read(); // receive byte as a character
    data[i] = c;
    i++;
  }
    first = data[0] - '0';
    second = data[1] - '0';
    third = data[2] - '0';
  }

  //Bluetooth
  if (EEBlue.available() > 0) // Send data only when you receive data:
  {
    input = EEBlue.readString(); //Read the incoming data and store it into variable data

    input.toCharArray(data,4);

    first = data[0] - '0';
    second = data[1] - '0';
    third = data[2] - '0';
  }
    Serial.print(first);
    Serial.print(second);
    Serial.print(third);
    Serial.print('\n');
  //pinMode(11, OUTPUT);  // Valve 2 Drink 1
  if (first > 0) { //output from drink 1
    
    digitalWrite(13, LOW);//pump on
    digitalWrite(11, LOW);//left valve on
//    delay(2000);
    delay((first*1850) + 2000); // dispense
    digitalWrite(11, HIGH);//left valve off
    
    digitalWrite(12, LOW); // air valve
    delay(5000); // clear water
    digitalWrite(13, HIGH); //pump off
    digitalWrite(12, HIGH);
//    first = 0;
  }

  //pinMode(10, OUTPUT); // Valve 3 Drink 2
  if (second > 0) { //output from drink 2
    
    digitalWrite(13, LOW);//pump on
    digitalWrite(10, LOW);//middle valve on
//    delay(2000);
    delay((second*1850) + 2000); // dispense
    digitalWrite(10, HIGH);//middle valve off

    digitalWrite(12, LOW); // air valve
    delay(5000); // clear water
    digitalWrite(13, HIGH); //pump off
    digitalWrite(12, HIGH);
//    second = 0;
  }

  //pinMode(9, OUTPUT); // Valve 4 Drink 3
  if (third > 0) { //output from drink 3
    
    digitalWrite(13, LOW);//pump on
    digitalWrite(9, LOW);//right valve on
//    delay(2000);
    delay((third*1850) + 2000); // dispense
    digitalWrite(9, HIGH);//right valve off

    digitalWrite(12, LOW); // air valve
    delay(5000); // clear water
    digitalWrite(13, HIGH); //pump off
    digitalWrite(12, HIGH);
//    third = 0;
  }

  // clear input data
  data[0] = '0';
  data[1] = '0';
  data[2] = '0';
  data[3] = '0';


}
