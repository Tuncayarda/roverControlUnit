#include "roverControlUnit.hpp"

// Setup function: Initializes servos, motor pins, and SPI communication.
void setup()
{
  // Attach each servo to its corresponding pin and set to initial position
  for (int i = 0; i < NUM_SERVO_PINS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(servoInitial[i]);
  }
  
  // Set motor control pins as OUTPUT and initialize with 0 (stopped)
  for (int i = 0; i < NUM_MOTOR_PINS; i++) {
    pinMode(motorPins[i], OUTPUT);
    analogWrite(motorPins[i], 0);
  }

  // Initialize SPI communication in mode 0 and enable SPI interrupt
  SPI.setDataMode(SPI_MODE0);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

// Main loop: Checks for incoming data and processes it if valid
void loop()
{
  // Proceed only if new data has been received
  if (dataReady)
  {
    dataReady = false;
    // Validate packet start (0xAA) and end markers (0xBB)
    if (buffer[0] == 0xAA && buffer[20] == 0xBB)
    {
      // Calculate checksum by XOR-ing bytes 1 to 18
      byte checksum = 0;
      for (int i = 1; i <= 18; i++)
        checksum ^= buffer[i];
      // Verify checksum matches the one in the received packet
      if (checksum == buffer[19])
      {
        // Process the valid data packet
        processData(buffer);
      }
    }
  }
}