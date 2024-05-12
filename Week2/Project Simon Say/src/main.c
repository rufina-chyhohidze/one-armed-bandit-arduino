#include <avr/io.h>
#include <avr/interrupt.h>
#include <led.h>
#include <buttons.h>
#include <usart.h>

//EXERCISE 1:PREPARATIONS TO PLAY
volatile uint8_t ledFlashing = 1; //it enable flashing LED 

// TURN ON pin change interrupt for a specific pin within the pin change interrupt group
void enablePinChangeInterrupt(int pinGroup, int pin) {
    if (pinGroup == 1) { // Example for PCINT1
        PCICR |= _BV(PCIE1); // Enable Pin Change Interrupt for group 1
        PCMSK1 |= _BV(pin); // Enable the specific pin within the group
    }
}

ISR(PCINT1_vect) {
    if (PINC & _BV(PC1)) { //if pc1 was pressed 
        ledFlashing = !ledFlashing; //then flash LED 4
    }
}

int main() 
{ 
    initUSART(); 
    DDRB |= _BV(PB5); // LED 4 as output

    enablePinChangeInterrupt(1, PC1); // Enable Pin Change Interrupt for PC1
  
    sei(); 
    
    while (1) 
    {
        if (ledFlashing) {
            PORTB ^= _BV(PB5); // Toggle LED 4
        }
        _delay_ms(300); 
    }
    return 0; 
}