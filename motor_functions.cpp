#include "Arduino.h"

#define MOTOR_LEFT_IN1 6
#define MOTOR_LEFT_IN2 7
#define MOTOR_RIGHT_IN1 2
#define MOTOR_RIGHT_IN2 3

void setupMotor(){
  pinMode(MOTOR_LEFT_IN1, OUTPUT);
  pinMode(MOTOR_LEFT_IN2, OUTPUT);
  pinMode(MOTOR_RIGHT_IN1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN2, OUTPUT);  
}

int speedToByteInt(int speed) {
  int bidirectionalSpeed;
  if(speed >= 100){
    bidirectionalSpeed = speed - 100;  
  } else {
    bidirectionalSpeed = (speed - 100) * -1;
  }
  // in low speeds, the wheels won't move. Thats why I added a min value
  int minByteValue = 80;

  return ((255 - minByteValue) / 100 * bidirectionalSpeed) + minByteValue;
}

void moveWheel(int speed, int MOTOR_IN1, int MOTOR_IN2) {
  int byteSpeed = speedToByteInt(speed);

  if(speed == 100) {
    analogWrite(MOTOR_IN1, 0);
    analogWrite(MOTOR_IN2, 0);
  } else if(speed > 100) {
    analogWrite(MOTOR_IN1, byteSpeed);
    analogWrite(MOTOR_IN2, 0);
  } else {
    analogWrite(MOTOR_IN1, 0);
    analogWrite(MOTOR_IN2, byteSpeed);
  }
}

void moveLeftWheel(int speed) {
  moveWheel(speed, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2);
}

void moveRightWheel(int speed) {
  moveWheel(speed, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2);
}
