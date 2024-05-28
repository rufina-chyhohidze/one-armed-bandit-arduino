#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <buttons.h>
#include <led.h>


//first version

/*When starting this program, LEDs PB2 and PB3 start flashing together on and off
 with an interval of 4 seconds (2 seconds together on, 2 seconds together off).*/

 /*
 When the user presses button PC1, an associated ISR starts.
  The ISR contains code that causes LEDs P3 and PB4 to flash together once on and off 
  with an interval of 10 seconds (5 seconds off, 5 seconds on) I DID LESS TIME,WAS TOO LONG )*/

volatile uint8_t ledStates[4] = {0, 0, 0, 0}; // LED states
volatile uint8_t ledFlashing[4] = {0, 0, 0, 0}; // LED flashing states

// Enable pin change interrupt for a specific pin within the pin change interrupt group
void enablePinChangeInterrupt(int pinGroup, int pin) {
    if (pinGroup == 1) { // Example for PCINT1
        PCICR |= _BV(PCIE1); // Enable Pin Change Interrupt for group 1
        PCMSK1 |= _BV(pin); // Enable the specific pin within the group
    }
}

// Pin Change Interrupt Service Routine
ISR(PCINT1_vect) {
    if (PINC & _BV(PC1)) { // Check if button 1 (PC1) was pressed
        // Toggle flashing for LED 2 and LED 3
        ledFlashing[1] = !ledFlashing[1];
        ledFlashing[2] = !ledFlashing[2];
        // Turn off flashing for LED 4
        ledFlashing[3] = 0; //set the according bit to 0
        // Wait for 5 seconds
        _delay_ms(2000);
        // Turn on flashing for LED 4
        ledFlashing[3] = 1; //set the according bit to 1
        _delay_ms(2000);
        ledFlashing[2] = 0;
        _delay_ms(2000);
        ledFlashing[2] = 1;

    }
}

int main() {
  DDRC &= ~_BV( PC1 );
  DDRB |= _BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5); // Set PB2, PB3, PB4, PB5 as output

    // Initially, both LEDs PB2 and PB3 flash together with a 4-second interval
    ledFlashing[1] = 1;
    ledFlashing[2] = 1;

    enablePinChangeInterrupt(1, PC1); // Enable Pin Change Interrupt for PC1

    sei(); // Enable global interrupts
    
    while (1) {
        for (int i = 0; i < 4; i++) {
            if (ledFlashing[i]) {
                ledStates[i] = !ledStates[i]; // Toggle LED state
            }
        }
        // Set LED states
        PORTB = (ledStates[0] << 1) | (ledStates[1] << 2) | (ledStates[2] << 3) | (ledStates[3] << 4);
        
        if (ledFlashing[1] && ledFlashing[2]) {
            _delay_ms(2000); // 2 seconds delay
        } else if (ledFlashing[3]) {
            _delay_ms(1000); // 1 seconds delay
        } else {
            _delay_ms(500); // 500 milliseconds delay
        }
    }
    return 0; 
} 

/* 
 Questions:
    - Does LED PB2 continue to flash when the ISR has started?
        No,but it remains enabled

    - Does LED D1 and D2 continue to flash after the ISR has been handled (ie is it over)?
        No, when the ISR is called, they stopped to flash together.

    - If LED D1 and D2 were on before starting the ISR, are they still on after running the ISR?
        - Yes,theyre enabled.

    - If LED D1 and D2 were off before starting the ISR, are they still off after running the ISR?
        - Its going to be only one, from the moment we start the second cycle.

    - If LEDs D1 and D2 were on for only 0.5 seconds before starting the ISR, will they keep their status for 1.5 seconds after performing the ISR?
        - PB2 will always remain on.

