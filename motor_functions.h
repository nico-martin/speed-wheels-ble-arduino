#ifndef MOTOR_FUNCTIONS_H
#define MOTOR_FUNCTIONS_H

void setupMotor();
void moveWheel(int speed, int MOTOR_IN1, int MOTOR_IN2);
int speedToByteInt(int speed);
void moveLeftWheel(int speed);
void moveRightWheel(int speed);

#endif
