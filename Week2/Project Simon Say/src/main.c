#include <avr/io.h>
#include <avr/interrupt.h>
#include <led.h>
#include <buttons.h>
#include <usart.h>
#include <stdlib.h> 

volatile uint8_t ledFlashing = 1; 
volatile uint8_t buttonPressed = 0; 
volatile uint8_t counter = 0; //counetr for gen.seeds 


void enablePinChangeInterrupt(int pinGroup, int pin) {
    if (pinGroup == 1) { 
        PCICR |= _BV(PCIE1); 
        PCMSK1 |= _BV(pin); 
    }
}

ISR(PCINT1_vect) {
    if (buttonPressed == 0 && (PINC & _BV(PC1))) { // check if button PC1 was pressed
        buttonPressed = 1; // //sets the state of button to 1 after pressing
    }
}

int main() 
{ 
    initUSART(); 
    DDRB |= _BV(PB5); 
    enablePinChangeInterrupt(1, PC1); 
    sei(); 
    
    while (1) 
    {
        if (ledFlashing) {
            PORTB ^= _BV(PB5); // Toggle LED 4
            _delay_ms(200); 
            counter++; // increments counter while LED is flashing
        }

        if (buttonPressed) {
            srand(counter);
            
            printf("Random Series: ");
            for (int i = 0; i < 10; i++) {
                uint8_t randomNum = rand() % 3; 
                printf("%d ", randomNum);
            }
            printf("\n");
            
            buttonPressed = 0; // Reset button state
        }
    }
    return 0; 
}