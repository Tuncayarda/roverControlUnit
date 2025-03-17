#include "roverControlUnit.hpp"

// Buffer to store incoming SPI data (21 bytes expected per packet)
volatile byte buffer[21];

// Flag to indicate when a full data packet has been received
volatile bool dataReady = false;

// Index to track the current position in the buffer
int index = 0;

// SPI interrupt service routine: triggered when a byte is received
ISR(SPI_STC_vect)
{
	// Read the incoming byte from SPI data register
	byte incoming = SPDR;

	// Store the byte in the buffer and increment the index
	buffer[index++] = incoming;
  
	// If a full packet is received, set the dataReady flag and reset index
	if (index >= 21) {
	  dataReady = true;
	  index = 0;
	}
}
