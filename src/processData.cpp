#include "roverControlUnit.hpp"

// Processes incoming data buffer to extract servo angles and motor values.
void processData(volatile byte* buffer)
{
	// Extract and constrain servo angles from buffer[1] to buffer[6]
	int servoAngles[6];
	for (int i = 0; i < 6; i++)
	  servoAngles[i] = constrain(buffer[1 + i], -45, 45);
	
	// Extract motor values from buffer[7] to buffer[18] (2 bytes per value)
	int motorValues[6];
	for (int i = 0; i < 6; i++)
	{
		// Combine two bytes into a 16-bit signed integer for each motor value
		int idx = 7 + i * 2;
		int16_t val = (buffer[idx] << 8) | buffer[idx + 1];
		
		// Constrain motor value to valid PWM range (-255 to 255)
		motorValues[i] = constrain(val, -255, 255);;
	}
	
	// Set servo angles
	setServos(servoAngles);
	
	// Drive motors with the processed values
	driveMotors(motorValues);
}