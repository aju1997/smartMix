# smartMix

smartMix is a system for quick, entertaining custom drink storage and dispensing. The drinks are poured within seconds and are accompanied by light effects to follow the flow of fluid and to notify the user of a complete pour.

# Arduino Code


## main.ino

This file is located in the arduino_code folder and again in the main folder. This file is used to take input signals from both the mobile application and the LCD screen to pour drinks out into the final output drink. If the signal is read from the mobile application, it will be read under the EEBlue.available(). If the LCD screen sends the data through I2C to the main.ino file, then it will be read from the Wire.onReceive(receiveEvent).

## Menus.h

This file is located in the arduino_code folder and in the lcd folder. This is a header file that contains all of the print statements for the lcd screen. It mirrors the code in lcd.ino sometimes taking in parameters such as current cursor position and outputs menu options. 

## lcd.ino

This file is located in the arduino_code folder and  in the lcd folder. This file contains the state machine for the lcd screen and displays the menu for our project. It also has code for the communication between the two arduinos using I2C. It sends a signal to pour a drink based on the option of being either custom or presets. It also stores custom drink data through the eeprom using write(). It includes a header file that allows it to print out the menu on the screen.


# Flutter Application
## All app files are located in the app folder

All files are all dependencies for the flutter framework.
Only modifications made and files added are under the lib folder
the other modification made was to the pubspec.yaml file. The 
changes done to the *.yaml file are to add plugins and dependencies
such as adding bluetooth package and firebase packages so that
it has support to Firebase database. 

## lib folder contents

### main.dart file

this contains the initial program that houses the main page. 

It is essentially the home page when the app opens up for the
first time.
This includes the ability to connect to a bluetooth device,
and list Most Used Drink, Custom Drinks, and Preset Drinks. 
This page also allows you to create custom drinks when selecting
the plus icon on top right.

Navigation drawer is in top left which allows user to navigate to
other pages. 

this file also contains the logic for age verifcation. as well
as pouring a drink, when the user selects an option. 

### newDrinkModal.dart file

this is the code that houses the custom drink page.
it can be reached by using either the plus button on top right
located on the home page, or by using the create mix option
in the navigation drawer. 

This file conains all the logic needed to custom made drinks
with user input, and send it to the database when complete. 

### listAllDrinks.dart

This page houses the list view of all custom drinks created. 

This page can be reached by opening the navigation drawer and
selecting the List Drinks option. 

This option will list all custom drinks the user has created, 
and also allows the user to create custom drinks by clicking
on the plus button on top right just like the home page. 

This page allows the user to also be able to dispense custom drinks
by simpling tapping on the custom drink they desire. It also
contains the logic for the age verification. 

### confirmModal.dart file located in /smartMix/app/lib/UI

this file simply contains the design for the alert popup that is
displayed when a user wants to dispense a drink

it is just a design file that gets called in the main pages. 

### drinkCard.dart file located in /smartMix/app/lib/UI

this file simply contains the design for the cards that are
displayed on the home page.

it is just a design file that gets called in on the main pages.
