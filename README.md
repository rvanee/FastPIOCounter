# Fast counter/timer for Arduino Nano RP2040 Connect


## Summary
 
 This is a simple sketch demonstrating the use of the RP2040 Programmable Input Output (PIO) to offer a high-resolution counter/timer (24ns resolution on Arduino Nano RP2040 Connect).


## Supported platforms

This sketch is designed to work on the Arduino Nano RP2040 Connect, using the Arduino IDE. It was tested on a board with firmware version 1.5.0 using Arduino IDE 2.2.1.
Since this version of the Arduino IDE does not provide pioasm, an assembled header file is included in this package.


## Usage

The sketch is self-explanatory. When using the counter in other scenarios, there is one important thing to keep in mind: counter overflow. The counter is only 32 bits, which overflows in 2^32 / (125MHz / 3) = 103s. There is overflow detection in the retrieve_counter() function, but it only works if subsequent calls are made within this interval.


## Explanation

The scratch X register is used to hold the main loop's start address, supplied by the user via the fifo upon initialization in order to account for program offset. If the fifo is empty, the OSR is filled with X, otherwise with a user-supplied adress of the start of the push sequence. The OSR content (address) determines whether to continue the main loop or to divert to the push sequence. The push sequence puts the two's complement (because the counter is decremented rather than incremented) of the scratch Y register, holding the 32 bit counter, in the fifo. Just as the main loop, the push sequence takes 3 cycles, which is why the push sequence includes its own counter decrement. Note that the counter will silently 'overflow' to zero, which should be handled by higher level code.
