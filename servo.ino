// Include libaries
#include <Servo.h> 

// Define pins for various purposes 
#define servoPin 10
#define sigPin 6
#define powerPin 7

// Define variables for various purposes
int sensorVal = LOW;

Servo servo;  // create servo object to control a servo


///////////// SETUP /////////////
void setup() {
  // Start serial for debugging and configuration of the sensor
  Serial.begin(9600);
  
  // Declare pins as outputs and inputs.
  pinMode(powerPin, OUTPUT);
  pinMode(sigPin, INPUT);

  // Set powerPin for the sensor to high to supply 5V through pin 7.
  digitalWrite(powerPin, HIGH);
  digitalWrite(sigPin, LOW);
}

///////////// LOOP /////////////
void loop() {
  
   servo.attach(servoPin);
   moveToLocation(95, 165, 1, 50); // From, To, Step Size, Stepdelay
   servo.detach();
   delay(10000);
   servo.attach(servoPin);
   moveToLocation(165, 95, 1, 50); // From, To, Step Size, Stepdelay
   servo.detach();
   delay(10000);
}

///////////// FUNCTION /////////////
void moveToLocation(int positionFrom, int positionTo, int stepSize, int stepDelay) {
  if (positionTo != positionFrom) {
    if (positionFrom < positionTo) {
      for (int i = positionFrom; i <= positionTo; i += stepSize) {
        servo.write(i);
        delay(stepDelay);
      }
    }
    else {
      for (int i = positionFrom; i >= positionTo; i -= stepSize) {
        servo.write(i);
        delay(stepDelay);
      }
    }
    if ((positionTo - positionFrom) % stepSize != 0) { // if traveled distance is not divisible by stepSize (for loop ends before servo reaches the final destination)
      servo.write(positionTo); // move the servo to the final postition
    }
  }
}
