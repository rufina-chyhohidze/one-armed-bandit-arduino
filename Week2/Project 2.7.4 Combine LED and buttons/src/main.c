#include <avr/io.h> 
#include <avr/interrupt.h> 
#include <util/delay.h> 
#include <usart.h> 
#include "buttons.h" 

volatile uint8_t ledStates[3] = {0, 0, 0}; // LED states
volatile uint8_t ledFlashing[3] = {0, 0, 0}; // LED flashing states

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
        ledFlashing[1] = !ledFlashing[1]; // Toggle flashing for LED 1
    }
    if (PINC & _BV(PC2)) { // Check if button 2 (PC2) was pressed
        ledFlashing[2] = !ledFlashing[2]; // Toggle flashing for LED 2
    }
}

int main() 
{ 
    initUSART(); 
    DDRB |= _BV(PB2); //controlling an LED
    DDRB |= _BV(PB3);
    DDRB |= _BV(PB4);

    enablePinChangeInterrupt(1, PC1); // Enable Pin Change Interrupt for PC1
    enablePinChangeInterrupt(1, PC2); // Enable Pin Change Interrupt for PC2
    
    sei(); // Enable global interrupts
    
    while (1) 
    {
        for (int i = 0; i < 3; i++) {
            if (ledFlashing[i]) {
                ledStates[i] = !ledStates[i]; // Toggle LED state
            }
        }

        PORTB = (ledStates[0] << 0) | (ledStates[1] << 1) | (ledStates[2] << 2); // Set LED states
        _delay_ms(500); // Flashing delay
    }
    return 0; 
}