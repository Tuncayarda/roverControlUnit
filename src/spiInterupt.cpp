#include "roverControlUnit.hpp"

// Buffer to store incoming SPI data (21 bytes expected per packet)
volatile byte buffer[21];
volatile bool dataReady = false;
volatile int index = 0;

// SPI interrupt service routine: triggered when a byte is received
ISR(SPI_STC_vect)
{
    byte incoming = SPDR;  // Incoming byte

    if (index < 21) {
        buffer[index++] = incoming;

        // If the first byte is received, immediately send ACK
        if (index == 1) {
            SPDR = 0x31;  // Send ACK in response to the first byte
        } else {
            SPDR = 0x21;  // Dummy response for other bytes (or additional info if needed)
        }

        // Is the entire packet received?
        if (index == 21) {
            dataReady = true;
            index = 0;  // Reset for new packet
        }
    } else {
        SPDR = 0x00;  // Dummy response in case of error
    }
}