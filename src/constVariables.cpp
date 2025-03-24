#include "roverControlUnit.hpp"

// Pin numbers for each servo motor
const int servoPins[] = {36, 34, 32, 42, 40, 38};

// Pin numbers for motor driver control (each motor has two pins: forward and backward)
const int motorPins[] = {2, 3, 5, 4, 6, 7, 13, 12, 10, 11, 9, 8};

// Array to store Servo objects for controlling individual servos
Servo servos[NUM_SERVO_PINS];

// Initial angle positions for each servo (used as base positions)
const int servoInitial[] = {70, 68, 69, 112, 125, 105};