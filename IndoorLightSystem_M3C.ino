// Outdoor System

// These constants won't change:
const int photoresistorPin = A0;   // pin that the sensor is attached to
const int Light_threshold = 400;  // an arbitrary threshold level that's in the range of the analog input
const int MOTION_THRESHOLD = 306; // Motion threshold CHANGE #
const int remotePin = A4; 
const int PIR_PIN = 8; // Passive infared pin

void int remotePresets();
int IR_SENSOR();
bool motionDetected();
bool lightLevel();

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communications:
  Serial.begin(9600);
}

void loop() {
 
  if (motionDetected == true && lightLevel == true) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

}

void int remotePresets() {

}

int IR_SENSOR() {

}

bool motionDetected() {
  int PIR_Value = analogRead(PIR_PIN);

  serial.println(PIR_Value);
  delay(1);

  if (PIR_Value > MOTION_THRESHOLD) {
    return true;
  }
  else {
    return false;
  }
}

bool lightLevel () {
 // read the value of the potentiometer:
  int analogValue = analogRead(photoresistorPin);

// print the analog value:
  Serial.println(analogValue);
  delay(1);  // delay in between reads for stability

  // if the analog value is high enough, turn on the LED:
  if (analogValue > Light_threshold) {
    return true;
  } 
  else {
    return false;
  }
}
