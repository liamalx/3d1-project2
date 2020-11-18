/*
 * Liam Alexander
 * IXD VDES20146 3D Design 1: Spatial Thinking and Materials
 * Project 2 – Sound
 * Fall 2020
*/
//-----------------------------------------------
//------Link to fritzing diagram of circuit------
//-----------------------------------------------
//Breadboard view: https://sheridanc-my.sharepoint.com/:i:/g/personal/alexalia_shernet_sheridancollege_ca/EUBjsMh3GEtDsMbzEtL2DJsBxA4s8kVpkr4Xq38cNjUSsA?e=gpFGNy
//-----------------------------------------------
//----------Link to Picture of circuit-----------
//-----------------------------------------------
//Overhead picture: https://sheridanc-my.sharepoint.com/:i:/g/personal/alexalia_shernet_sheridancollege_ca/Eci97a0RJ_hJvvtTgcOo1q0BuTzAxTwCWGMNlIEmAkWhyw?e=e3aCIS
//-----------------------------------------------
//-----------------General notes-----------------
//-----------------------------------------------
// HARDWARE USED:
/* - arduino UNO  
 * - 2x 10k resistor
 * - 220 resistor
 * - 2 momentary pushbutton
 * - ultrasonic sensor (HC-SR04)
 * - 16x2 lcd display
 * - 8ohm speaker
 * - aligator clips
 * - lots of wire
 * - 2x small breadboard
*/

// HOW TO USE CIRCUIT

//MODE 1 (sound)
/* First press the start button
 * Move obj (hand or flat surface) towards and away from ultrasonic
 * sensor to change distance reading to produce sound
*/
// MODE 2 (MUTE)
// To mute the circuit press the mute button

//-----------------------------------------------
//-Resources refrenced / sources for inspiration-
//-----------------------------------------------
/*
 * Hello world LCD example : https://www.arduino.cc/en/Tutorial/LibraryExamples/HelloWorld
 * Button debounce example : https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
 * ultrasonic sensor and lcd example : https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
 * ultrasonic reading to notes : https://www.instructables.com/Ultrasonic-Theremin-Teach-Sound/
 * Switch case refrence: https://www.arduino.cc/reference/en/language/structure/control-structure/switchcase/
 * noTone refrence :https://www.arduino.cc/reference/en/language/functions/advanced-io/notone/
*/

//#include "pitches.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); // RS, EN, D4, D5, D6, D7

const int speaker = 7;
int mode;

//ultrasonic sensor varibles
//long duration; // variable for the duration of sound wave travel
int distance_cm; // variable for centimeters measurement
int distance_inch; // variable for inches measurement
long duration, inches, cm;

//ultrasonic sensor pin numbers
const int triggerPin = 5;
const int echoPin = 6;

//button costant pin numbers
const int buttonPitch=2;
const int buttonRec=3;
const int buttonPlay=4;

//Button state varibles
int buttonPitchState;
int buttonRecState;
int buttonPlayState;

//Button LAST state varibles *REFRENCED FROM BUTTON DEBOUNCE*
int lastButtonPitchState = LOW;
int lastButtonRecState = LOW;
int lastButtonPlayState = LOW;

//***directly from debounce source***
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
//***end of deobuce source***

int melody[50];
unsigned long previousMillis = 0;    

//sourced from https://github.com/robsoncouto/arduino-songs  
//int notes = sizeof(melody) / sizeof(melody[0]) / 2;

void setup() {
  
Serial.begin(9600);

//button pinmodes
  pinMode(buttonPitch,INPUT);
  pinMode(buttonRec,INPUT);
  pinMode(buttonPlay,INPUT);
  
//ultrasonic sensor pinmodes
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);

  lcd.begin(16, 2); // lcd starts with resolution 16x2
  
}

void loop() {

 
unsigned long currentMillis = millis();

int buttonPitchState = digitalRead(buttonPitch);
int buttonRecState = digitalRead(buttonRec);
int readingPlayState = digitalRead(buttonPlay);
int pitch;
ultrasonicReading();
pitch = constrain(map(cm, 1, 40, 256, 523), 220, 523);
      
      if (buttonPitchState == HIGH) {
        noTone(speaker);
        mode=1;
        Serial.println("pitch on");
      }
      else if (buttonRecState == HIGH) {
        noTone(speaker);
        
        mode=2;
        Serial.println("rec on");
      }


switch(mode){

  case 1:
    Serial.println("mode 1");
    tone(speaker,pitch);
    Serial.println(pitch);
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(cm);
    lcd.println(" cm  ");
    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(inches);
    lcd.println(" inch  ");
    break;
    
  case 2:
    Serial.println("mode 2");
lcd.setCursor(0, 0);
lcd.print("Speaker muted     ");
lcd.setCursor(0, 1);
lcd.print("                             ");  
    break;
    
  default:
  break;
}//end of switch statment for mode


}//end of void loop

void ultrasonicReading(){

//  long duration, inches, cm;
   pinMode(triggerPin, OUTPUT);
   digitalWrite(triggerPin, LOW);
   delayMicroseconds(2);
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   delay(100);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
