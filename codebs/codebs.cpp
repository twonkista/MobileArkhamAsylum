#define SERVO_PIN  18

Servo myServo;
#include <ESP32Servo.h>

enum State {
  UNITIALIZED,
  HOUR2MODE,
  HOUR8MODE
};

State currentState = UNITIALIZED;

unsigned long stateStartTime = 0;
unsigned int hour2button = 12;
unsigned int hour8button = 10;
const unsigned long eightHours = 28800;
const unsigned long twohours = 7200;
bool doneCond = true;

const int LOCK_POS = 0;
const int UNLOCK_POS = 90;


void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);  // Example LED
  pinMode(hour2button, INPUT_PULLUP);
  pinMode(hour8button, INPUT_PULLUP);
  myServo.attach(SERVO_PIN);
  myServo.write(UNLOCK_POS);
  stateStartTime = millis();
}

void loop() {
  handleState();
}

void handleState() {
  switch (currentState) {
    case UNITIALIZED:
      Serial.println("UNLOCKED MODE");

      if (digitalRead(hour2button) == LOW) {
        transitionTo(HOUR2MODE);
        unlocked = false; 
        myServo.write(LOCK_POS);
        Serial.println("WAIT 2 HOURS");
      }
      if (digitalRead(hour8button) == LOW) {
        transitionTo(HOUR8MODE);
        doneCond = false; 
        myServo.write(LOCK_POS);
        Serial.println("WAIT 8 HOURS");
      }
    break;


    case HOUR8MODE:
      if (millis() - stateStartTime >= twoHours) {
        transitionTo(UNITIALIZED);
        doneCond = true;
        myServo.write(UNLOCK_POS);
      }
      break;


    case HOUR2MODE:
      if (millis() - stateStartTime >= twoHours) {
        transitionTo(UNITIALIZED);
        doneCond = true;
        myServo.write(UNLOCK_POS);
      }
      break;
  }
}


void transitionTo(State newState) {
  currentState = newState;
  stateStartTime = millis();
  Serial.print("Transitioning to state: ");
  Serial.println(currentState);
}