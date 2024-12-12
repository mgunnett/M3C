/*
 * File: OutdoorSystem_M3C.ino
 * Authors: Parker West & Megan Gunnett
 * Date: 12/18/2024
 * Description: This Arduino project is the control system for the outdoor lights. The lights utilize the use of a PIR sensor, an IR remote reciever, 
 *              and a photoresistor. This program uses the IRremote.hpp library to control the remote. For more information on this library, visit 
                https://github.com/Arduino-IRremote/Arduino-IRremote.git.
 */
#include <IRremote.hpp>

// These constants won't change:
const int PR_PIN          =  A0;   // pin that the photoresistor is in
const int IR_RECEIVE_PIN  =   4;
const int LIGHT_THRESHOLD = 400;   // an arbitrary threshold level that's in the range of the analog input
const int PIR_PIN         =   8;     // Passive infared pin
const int LED_PIN         =  12;
const int ERROR           =  -1;  //an error message for debugging purposes

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
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(PR_PIN, INPUT);
  //initialize the IR reciever (using the IRremote library)
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

//functions as an `int main()`
//these programs will loop continously and 'control' the arduino
void loop() {
 
  //first, detect if the light level is high enough and detect motion
  if (motionDetected() == true && lightLevel() == true) {
    digitalWrite(LED_PIN, HIGH); //power on LED
    remotePresets();
  }
  else { //then either no motion is detected or the light level is too high
    digitalWrite(LED_PIN, LOW); //power off LED
  }
 


printValues(); //display sensor values for debugging
delay(15); //delay to aid in logic

}



int remotePresets() {
  if (IrReceiver.decode()){ //if a signal is recieved, decode the recieved signal to a hexadecimal value
    uint16_t command = IrReceiver.decodedIRData.command; //converts signal into an integer value. Stored in a structure.
    //usually, the signal would be printed in the command line. The print commands are in printValues()

    /* decode the integer signal using the table values below:
  
                      | Button | Code | 
                          | 0 |  22 |
                          | 1 |  12 |
                          | 2 |  24 |
                          | 3 |   9 |
                          | 4 |   8 |
                          | 5 |  28 |
                          | 6 |  90 |
                          | 7 |  66 |
                          | 8 |  82 |
                          | 9 |  74 |
  */
    //run a switch statement. Returns the button pressed
    switch (command){
      case 22: //button #0
        return 0;
      case 12: //button #1
        return 1;
      case 24: //button #2
        return 2;
      case 9: //button #3
        return 3;
      case 8: //button #4
        return 4;
      case 28: //button #5
        return 5;
      case 90: //button #6
        return 6;
//add more cases for more buttons

      
      default: 
        return ERROR;
      
    }

    delay(100); 
    IrReceiver.resume();

  }


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
  int PRValue = analogRead(PR_PIN);

  // if the analog value is high enough, turn on the LED:
  if (PRValue > LIGHT_THRESHOLD) {
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
  int PRValue = analogRead(PR_PIN);
  Serial.print("  Photoresistor Value: ");
  Serial.print(PRValue);
   Serial.print("  \n"); //print space between each sensor value and then a new line

  //wait .3 seconds for readability
  delay(300);
}