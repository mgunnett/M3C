/*
  Conditionals - If statement

  This example demonstrates the use of if() statements.
  It reads the state of a potentiometer (an analog input) and turns on an LED
  only if the potentiometer goes above a certain threshold level. It prints the
  analog value regardless of the level.

  The circuit:
  - potentiometer
    Center pin of the potentiometer goes to analog pin 0.
    Side pins of the potentiometer go to +5V and ground.
  - LED connected from digital pin 13 to ground through 220 ohm resistor

  - Note: On most Arduino boards, there is already an LED on the board connected
    to pin 13, so you don't need any extra components for this example.

  created 17 Jan 2009
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ifStatementConditional
*/

// These constants won't change:
const int photoresistorPin = A0;   // pin that the sensor is attached to
const int threshold = 400;  // an arbitrary threshold level that's in the range of the analog input
const int rgb_Blue = A9, // pin the rgb led's are attached to
          rgb_Green = A10,
          rgb_Red = A11;
const int remotePin = A4;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communications:
  Serial.begin(9600);
}

void loop() {
  // read the value of the potentiometer:
  int analogValue = analogRead(potentiomometerPin);

  // if the analog value is high enough, turn on the LED:
  if (analogValue > threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // print the analog value:
  Serial.println(analogValue);
  delay(1);  // delay in between reads for stability
}

void RGBcolor() {
  
}
