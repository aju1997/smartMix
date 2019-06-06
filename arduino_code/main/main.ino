#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String input = "";
char data[4];
SoftwareSerial EEBlue(3, 4);

void setup()
{ 
  //Sets the data rate in bits per second (baud) for serial data transmission
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

  //Slave Receiver
  Wire.begin(8);                // join i2c bus with address #8
}

int drink1[3] = {2000, 5000, 10000};
int drink2[3] = {7000, 4000, 9000};
int drink3[3] = {2000, 5000, 3000};
int first = 0;
int second = 0;
int third = 0;

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all except last character
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
}

void loop()
{
  //LCD
  Wire.requestFrom(2, 3);    // request 6 bytes from slave device #2
  int i = 0;
  while(Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read();    // receive a byte as character
    data[i] = c;
    ++i;
    Serial.print(c);         // print the character
  }

  //Bluetooth
  if (EEBlue.available() > 0) // Send data only when you receive data:
  {
    input = EEBlue.readString(); //Read the incoming data and store it into variable data

    input.toCharArray(data,4);
  }
  first = data[0] - '0';
  second = data[1] - '0';
  third = data[2] - '0';
  
  if (first > 0) { 
    //output from drink 1
    Serial.print("Drink 1 output\n");
    Serial.print(first);
    Serial.print(second);
    Serial.print(third);
    Serial.print('\n');
    
    digitalWrite(13, LOW);//pump on
    digitalWrite(11, LOW);//left valve on
    delay(2000);
    delay(first*1850); // dispense
    digitalWrite(11, HIGH);//left valve off
    
    digitalWrite(12, LOW); // air valve
    delay(5000); // clear waterv
    digitalWrite(13, HIGH); //pump off
    digitalWrite(12, HIGH);
    first = 0;
  }
  
  if (second > 0) { 
    //output from drink 2
    Serial.print("Drink 2 output\n");
    Serial.print(first);
    Serial.print(second);
    Serial.print(third);
    Serial.print('\n');
    
    digitalWrite(13, LOW);//pump on
    digitalWrite(10, LOW);//middle valve on
    delay(2000);
    delay(second*1850); // dispense
    digitalWrite(10, HIGH);//middle valve off

    digitalWrite(12, LOW); // air valve
    delay(5000); // clear water
    digitalWrite(13, HIGH); //pump off
    digitalWrite(12, HIGH);
    second = 0;
  }

  if (third > 0) { //output from drink 3
    Serial.print("Drink 3 output\n");
    Serial.print(first);
    Serial.print(second);
    Serial.print(third);
    Serial.print('\n');
    
    digitalWrite(13, LOW);//pump on
    digitalWrite(9, LOW);//right valve on
    delay(2000);
    delay(third*1850); // dispense
    digitalWrite(9, HIGH);//right valve off

    digitalWrite(12, LOW); // air valve
    delay(5000); // clear water
    digitalWrite(13, HIGH); //pump off
    digitalWrite(12, HIGH);
    third = 0;
  }

  // clear input data
  data[0] = '0';
  data[1] = '0';
  data[2] = '0';
  data[3] = '0';

}
