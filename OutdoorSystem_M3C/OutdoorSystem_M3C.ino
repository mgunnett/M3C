/*
 * File: OutdoorSystem_M3C.ino
 * Authors: Parker West & Megan Gunnett
 * Date: 12/18/2024
 * Description: This Arduino project is the control system for the outdoor lights. The lights utilize the use of a PIR sensor, an IR remote reciever, 
 *              and a photoresistor. This program uses the IRremote.hpp library to control the remote. 
 */
#include <IRremote.hpp>

// These constants won't change:
const int photoresistorPin = A0;   // pin that the sensor is attached to
const int remotePin       =  A4; 
const int Light_threshold = 400;   // an arbitrary threshold level that's in the range of the analog input
const int PIR_PIN         =   8;     // Passive infared pin
const int ledPin          =  13;

//function prototypes, all used without callbacks
int remotePresets();
int IR_SENSOR();
bool motionDetected();
bool lightLevel();
void printValues();

void setup() {
  // initialize serial communications at 9600 bits per second:
  Serial.begin(9600);

  // initialize pins for input/output:
  pinMode(ledPin, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(photoresistorPin, INPUT);
}

//functions as an `int main()`
//these programs will loop continously and 'control' the arduino
void loop() {
 
  //first, detect if the light level is high enough and detect motion
  if (motionDetected() == true && lightLevel() == true) {
    digitalWrite(ledPin, HIGH); //power on LED
  }
  else { //then either no motion is detected or the light level is too high
    digitalWrite(ledPin, LOW); //power off LED
  }
 
printValues(); //display sensor values for debugging
delay(15); //delay to aid in logic

}



int remotePresets() {

}



int IR_SENSOR() {

}



bool motionDetected() {
 int PIR_Value = digitalRead(PIR_PIN);

  if (PIR_Value == 1) {
    return true;
  }
  else {
    return false;
  }
}
/*         Name: lightLevel()
*       Purpose: Detects the light level and compares it to a predefined threshold.
 *       @param: N/A
 *       Return: bool- returns true when the light level is above a threshold (when darker), returns
 *                     false when the light level is below a threshold. 
 */
bool lightLevel () {
 // read the value of the potentiometer:
  int PRValue = analogRead(photoresistorPin);

  // if the analog value is high enough, turn on the LED:
  if (PRValue > Light_threshold) {
    return true;
  } 
  else {
    return false;
  }
}


/*         Name: printValues()
*       Purpose: Prints the values of all the sensors in the serial monitor for easy debugging.
 *       @param: N/A
 *       Return: N/A- runs line of code without a return. 
 */
void printValues(){
  //PIR Values
  int PIR_Value = digitalRead(PIR_PIN);
  Serial.print("PIR Value: ");
  Serial.print(PIR_Value);

  //photoresistor values
  int photoresistorValue = analogRead(photoresistorPin);
  Serial.print("  Photoresistor Value: ");
  Serial.print(photoresistorValue);
   Serial.print("  \n"); //print space between each sensor value and then a new line

  //wait .3 seconds for readability
  delay(300);
}