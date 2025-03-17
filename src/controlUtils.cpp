#include "roverControlUnit.hpp"

// Controls the drive motors based on provided speed values.
// motorValues: An array of 6 integers representing motor speeds (-255 to 255) for each motor.
// Positive values drive the motor forward, negative values drive it backward, and 0 stops it.
void driveMotors(int* motorValues)
{
  // Mapping of motor index to its corresponding forward and backward control pin indices.
  int motorPinIndices[6][2] = {
    {RF_F, RF_B},
    {RM_F, RM_B},
    {RB_F, RB_B},
    {LF_F, LF_B},
    {LM_F, LM_B},
    {LB_F, LB_B}
  };

  for (int i = 0; i < 6; i++) {
    // Retrieve speed value and corresponding motor control pins
    int val = motorValues[i];
    int forwardPin = motorPins[motorPinIndices[i][0]];
    int backwardPin = motorPins[motorPinIndices[i][1]];

    // Drive motor forward with PWM signal proportional to val
    if (val > 0 && val <= 255) {
      analogWrite(forwardPin, val);
      analogWrite(backwardPin, 0);
    } 
    // Drive motor backward with PWM signal proportional to absolute value of val
    else if (val < 0 && val >= -255) {
      analogWrite(forwardPin, 0);
      analogWrite(backwardPin, -val);
    } 
    // Stop motor by setting both control pins to 0
    else {
      analogWrite(forwardPin, 0);
      analogWrite(backwardPin, 0);
    }
  }
}

// Sets servo positions based on provided angle offsets.
// angles: An array of integers representing the angle offset for each servo.
// The actual angle is calculated as initial angle + offset.
void setServos(int* angles)
{
  // Iterate through all servos and set their angles
  for (int i = 0; i < NUM_SERVO_PINS; i++)
    servos[i].write(servoInitial[i] + angles[i]);
}