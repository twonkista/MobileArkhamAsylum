#inlude <ESP32Servo.h>


Servo myServo
int servoPin = 18;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(servoPin);
  myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
