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
const int Light_threshold = 200;   // an arbitrary threshold level that's in the range of the analog input
const int PIR_PIN         =   8;     // Passive infared pin
const int ledPin          =  13;

int remotePresets();
int IR_SENSOR();
bool motionDetected();
bool lightLevel();
void printValues();

void setup() {
  // initialize serial communications:
  Serial.begin(9600);

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(photoresistorPin, INPUT);
  
}

//functions as an `int main()`
void loop() {
 
  if (motionDetected() == true && lightLevel() == true) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
 
printValues();
delay(15); //delay to aid in infinate logic

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


/*        Name: printValues()
 *       @param: N/A
 *  Description: Prints the values of all the sensors in the serial monitor for easy debugging
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