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
    
    first = data[0] - '0';
    second = data[1] - '0';
    third = data[2] - '0';

  //pinMode(11, OUTPUT);  // Valve 2 Drink 1
  if (first > 0) { //output from drink 1
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
    delay(5000); // clear water
    digitalWrite(13, HIGH); //pump off
    digitalWrite(12, HIGH);
  }

  //pinMode(10, OUTPUT); // Valve 3 Drink 2
  if (second > 0) { //output from drink 2
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
  }

  //pinMode(9, OUTPUT); // Valve 4 Drink 3
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
  }

  data[0] = '0';
  data[1] = '0';
  data[2] = '0';
  data[3] = '0';


  }

}