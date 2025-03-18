#include "roverControlUnit.hpp"

// Processes incoming data buffer to extract servo angles and motor values.
void processData(volatile byte* buffer)
{
	// Extract and constrain servo angles from buffer[1] to buffer[6]
	int servoAngles[6];
	for (int i = 0; i < 6; i++) {
		int8_t signedByte = static_cast<int8_t>(buffer[1 + i]);
		servoAngles[i] = constrain(signedByte, -45, 45);
	}
	
	// Extract motor values from buffer[7] to buffer[18] (2 bytes per value)
	int motorValues[6];
	for (int i = 0; i < 6; i++)
	{
		int idx = 7 + i * 2;

		// buffer[idx] -> Low byte, buffer[idx+1] -> High byte
		uint8_t lowByte = buffer[idx];
		uint8_t highByte = buffer[idx + 1];

		// Combine bytes into int16_t (signed)
		int16_t val = (int16_t)((highByte << 8) | lowByte);

		motorValues[i] = constrain(val, -255, 255);
	}
	
	// Set servo angles
	setServos(servoAngles);
	// Drive motors with the processed values
	driveMotors(motorValues);
}