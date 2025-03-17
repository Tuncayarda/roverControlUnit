
#ifndef ROVERCONTROLUNIT_HPP
# define ROVERCONTROLUNIT_HPP
# include <Arduino.h>
# include <Servo.h>
# include <SPI.h>

#define NUM_SERVO_PINS 6
#define NUM_MOTOR_PINS 12

enum ServoIndex{
  LF, // Left Middle
  LM, // Left Back
  LB, // Left Front
  RF, // Right Back
  RM, // Right Middle
  RB  // Right Front
};

enum MotorIndex{
  LF_F, // Left Middle - Back
  LF_B, // Left Middle - Front
  LM_F, // Right Back - Front
  LM_B, // Right Back - Back
  LB_F, // Right Middle - Front
  LB_B, // Right Middle - Back
  RF_F, // Left Back - Back
  RF_B, // Left Back - Front
  RM_F, // Left Front - Back
  RM_B, // Left Front - Front
  RB_F, // Right Front - Back
  RB_B  // Right Front - Front
};

void driveMotors(int* motorValues);
void setServos(int* angles);
void processData(volatile byte* buffer);

extern const int servoPins[NUM_SERVO_PINS];
extern const int motorPins[NUM_MOTOR_PINS];
extern Servo servos[NUM_SERVO_PINS];
extern const int servoInitial[NUM_SERVO_PINS];
extern volatile byte buffer[21];
extern volatile bool dataReady;

#endif