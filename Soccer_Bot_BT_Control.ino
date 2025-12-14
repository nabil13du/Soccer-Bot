#include <SoftwareSerial.h>

#define RPWM_L 9
#define LPWM_L 3
#define RPWM_R 6
#define LPWM_R 5

SoftwareSerial BTSerial(10, 11);

void setup() {
  pinMode(RPWM_L, OUTPUT);
  pinMode(LPWM_L, OUTPUT);
  pinMode(RPWM_R, OUTPUT);
  pinMode(LPWM_R, OUTPUT);

  BTSerial.begin(9600);
  Serial.begin(9600);

  stopMotors();
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read();
    Serial.println(command);

    switch (command) {
      case 'T': moveForward(160); break;
      case 'X': moveBackward(160); break;
      case 'R': turnRight(120, 500); break;
      case 'L': turnLeft(120, 500); break;
      case 'F': moveForward(255); break;
      case 'B': moveBackward(255); break;
      case 'P': slowRight(); break;
      case 'A': slowLeft(); break;
      default: stopMotors(); break;
    }
  }
}

void moveForward(int speed) {
  analogWrite(LPWM_L, 0);
  analogWrite(LPWM_R, 0);
  analogWrite(RPWM_L, speed);
  analogWrite(RPWM_R, speed);
}

void moveBackward(int speed) {
  analogWrite(RPWM_L, 0);
  analogWrite(RPWM_R, 0);
  analogWrite(LPWM_L, speed);
  analogWrite(LPWM_R, speed);
}

void turnLeft(int speed, int duration) {
  analogWrite(RPWM_L, 0);
  analogWrite(LPWM_R, 0);
  analogWrite(LPWM_L, speed);
  analogWrite(RPWM_R, speed);
  delay(duration);
  stopMotors();
}

void turnRight(int speed, int duration) {
  analogWrite(LPWM_L, 0);
  analogWrite(RPWM_R, 0);
  analogWrite(RPWM_L, speed);
  analogWrite(LPWM_R, speed);
  delay(duration);
  stopMotors();
}

void slowRight() {
  analogWrite(LPWM_L, 0);
  analogWrite(LPWM_R, 0);
  analogWrite(RPWM_L, 80);
  analogWrite(RPWM_R, 160);
}

void slowLeft() {
  analogWrite(LPWM_L, 0);
  analogWrite(LPWM_R, 0);
  analogWrite(RPWM_L, 160);
  analogWrite(RPWM_R, 80);
}

void stopMotors() {
  analogWrite(LPWM_L, 0);
  analogWrite(LPWM_R, 0);
  analogWrite(RPWM_L, 0);
  analogWrite(RPWM_R, 0);
}
