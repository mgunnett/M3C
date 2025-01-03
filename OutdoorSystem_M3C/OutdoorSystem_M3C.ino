/*
 * File: OutdoorSystem_M3C.ino
 * Authors: Parker West & Megan Gunnett
 * Date: 12/18/2024
 * Description: This Arduino project is the control system for the outdoor lights. The lights utilize the use of a PIR sensor, an IR remote reciever, 
 *              and a photoresistor. This program uses the IRremote.hpp library to control the remote. For more information on this library, visit 
                https://github.com/Arduino-IRremote/Arduino-IRremote.git. This program also sues the millisDelay library to control the use of a timer.
 */
#include <IRremote.hpp>
#include <millisDelay.h>

millisDelay ledDelay; //declare the millisecond delay for the LED

// These constants won't change:
const int PR_PIN          =  A0;  // pin that the photoresistor is in
const int IR_RECEIVE_PIN  =   4;   
const int PIR_PIN         =   8;  // Passive infared pin
const int LED_PIN         =  10;  // A PWM pin so birghtness can be adjusted
const int LIGHT_THRESHOLD = 350;  // an arbitrary threshold level that's in the range of the analog input
const int ERROR           =  -1;  // an error message for debugging purposes
const int PWR             = 999;  // defines power button as an integer
      int counter         =   1;  // A counter to keep track of the number of PWR button presses

//function prototypes, see below loop() for definitions
int remoteInput();
bool motionDetected();
bool lightLevel();
void printValues(int button);
void remotePresets(int button);

void setup() {
  // initialize serial communications at 9600 bits per second
  Serial.begin(9600);

  // initialize pins for input/output
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(PR_PIN, INPUT);
  
  //seed the RNG... used for the candle preset in remotePresets
  randomSeed(analogRead(0));

  //initialize the IR reciever (using the IRremote library)
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

//functions as an 'int main()'
//these programs will loop continously and 'control' the arduino
void loop() {
  int button = remoteInput(); //define button as the current remote input
  remotePresets(button); //check which preset to run based on button value
  printValues(button); //display sensor values for debugging
  delay(15); //delay to aid in logic
}

/*         Name: remotePresets()
 *      Purpose: Recieves signal from the IR remote and decodes them into a useable integer. Most code in this function
 *               is derived from the IRreciever library.
 *       @param: N/A
 *       Return: int- Returns an integer code that can be used to program remote presets 
 */
int remoteInput() {
  if (IrReceiver.decode()){ //if a signal is recieved, decode the recieved signal to a hexadecimal value
    uint16_t command = IrReceiver.decodedIRData.command; //converts signal into an integer value. Stored in a structure.
    //usually, the signal would be printed in the command line. The print commands are in printValues()
    /* 
    decode the integer signal using the table values below:
  
                      | Button | Code | 
                      |      0 |  22 |
                      |      1 |  12 |
                      |      2 |  24 |
                      |      3 |  94 |
                      |      4 |   8 |
                      |      5 |  28 |
                      |      6 |  90 |
                      |      7 |  66 |
                      |      8 |  82 |
                      |      9 |  74 |
                      |     PWR|  69 | 
  */
    delay(15); 
    IrReceiver.resume();
    //run a switch statement. Returns the button pressed
    switch (command){
      case 22: //button #0
        return 0;
      case 12: //button #1
        return 1;
      case 24: //button #2
        return 2;
      case 94: //button #3
        return 3;
      case 8: //button #4
        return 4;
      case 28: //button #5
        return 5;
      case 90: //button #6
        return 6;
      case 66: //button #7
        return 7;
      case 82: //button #8
        return 8;
      case 74: //button #9
        return 9;   
      case 69: //PWR button
        counter++;
        return PWR;
      default: //then an unknown signal is recieved
        return ERROR;
    } //end of switch
  } 


}
/*         Name: remotePresets
 *      Purpose 
 *       @param: int button- the number of the pressed button (numbers 0-9, PWR button)
 *       Return: N/A- runs line of code without a return. 
 */
void remotePresets(int button){
  /* 
   decode the integer signal using the table values below:
                     | Button |    Preset      | 
                     |      0 | Motion Sensor  |
                     |      1 | Low Brightness |
                     |      2 | Mid Brightness |
                     |      3 | High Brightness|
                     |      4 | Slow Fade      |
                     |      5 | Mid Fade       |
                     |      6 | Fast Fade      |
                     |      7 | Candle         |
                     |      8 | N/A            |
                     |      9 | N/A            |
                     |     PWR| Manual On/Off  | 
  */
  //run a switch statment. Runs a preset based on the button inputed:
  switch (button){
    case 0: //the motion sensor code, inputting other codes will ovveride this code
       if (motionDetected() == true && lightLevel() == true) { //check if the light level is low enough and motion is detected
      digitalWrite(LED_PIN, HIGH);
      ledDelay.start(5000); //set a timer for 15 seconds
      }
      break;

    case 1: //low brightness. Since LED_PIN is a PWM pin, we can use analogWrite
      analogWrite(LED_PIN, 20); 
      break;

 case 2: //mid brightness
      analogWrite(LED_PIN, 100);
      break;

 case 3: //high brightness
      analogWrite(LED_PIN, 255);
      break;

 case 4: //slow fade
     //fade the LED brighter first
     for (int i = 0; i <= 255; i++){
      analogWrite(LED_PIN, i);
      //check for remote input to exit a long loop
      if (IrReceiver.decode()) break;
      delay(20); //wait 20 msec
     }
     //now fade the LED dimmer
     for (int i = 255; i >= 0; i--){
      analogWrite(LED_PIN, i);
      if (IrReceiver.decode()) break;
      delay(20); //wait 20 msec
     }
      break;

 case 5: //mid fade
     //fade the LED brighter first
     for (int i = 0; i <= 255; i++){
      analogWrite(LED_PIN, i);
      //check for remote input to exit a long loop
      if (IrReceiver.decode()) break;
      delay(10); //wait 10 msec
     }
     //now fade the LED dimmer
     for (int i = 255; i >= 0; i--){
      analogWrite(LED_PIN, i);
      if (IrReceiver.decode()) break;
      delay(10); //wait 10 msec
     }
     //enter preset
      break;

 case 6: //fast fade
     //fade the LED brighter first
     for (int i = 0; i <= 255; i++){
      analogWrite(LED_PIN, i);
      //check for remote input to exit a long loop
      if (IrReceiver.decode()) break;
      delay(5); //wait 20 msec
     }
     //now fade the LED dimmer
     for (int i = 255; i >= 0; i--){
      analogWrite(LED_PIN, i);
      if (IrReceiver.decode()) break;
      delay(5); //wait 20 msec
     }
      break;

 case 7: //candle effect, uses a RNG to control the brightness
    while(true){
        int flicker = random(75, 150);
        analogWrite(LED_PIN, flicker);
        if (IrReceiver.decode()) break;
        delay(random(10, 100));
      }
    break;

 case 8:
     //intentionally left blank
      break;
 case 9:
     //intentionally left blank
      break;

 case PWR:
      //turn the lights on and off again, depending on the value of counter
      if (counter % 2 == 1){ //if counter is odd, then turn on the lights
        digitalWrite(LED_PIN, HIGH);
      }
      else {
        digitalWrite(LED_PIN, LOW);
      }
      break;

  default: //then the remote has received an error
    break;
  }
  //put the code to turn off the motion-powered lights here so they will always check
  if (ledDelay.justFinished()) {
          digitalWrite(LED_PIN, LOW); //power off LED
  }
}

/*         Name: motionDetected
 *      Purpose: Detects if motion is around the sensor (using 0 for fale, 1 for true)
 *       @param: N/A
 *       Return: bool- returns true when motion is detected, returns false when none is detected
 */
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
void printValues(int button){
  //PIR Values
  int PIR_Value = digitalRead(PIR_PIN);
  Serial.print("PIR Value: ");
  Serial.print(PIR_Value);

  //photoresistor values
  int PRValue = analogRead(PR_PIN);
  Serial.print("  Photoresistor Value: ");
  Serial.print(PRValue);

  //remote input values
  Serial.print ("  Remote Button Input: ");
  if (button == ERROR){ //print if there was an error with the signal
    Serial.print("ERROR");
  }
  else if (button == PWR){ //print if the PWR button was pressed
    Serial.print("PWR");
  }
  else { //print which button was pressed
    Serial.print(button);
  }
  Serial.print("  :-)\n"); //print space between each sensor value and then a new line

  //wait .3 seconds for readability
  delay(300);
}