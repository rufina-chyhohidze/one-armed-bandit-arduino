#include <buttons.h>

void enableButton( int button ){
    DDRC &= ~_BV( button );
    PORTC |= _BV( button ); 
} ;
int buttonPushed( int button ){
    if (bit_is_clear(PINC, button)) { 
        return 1; // Button is pressed 
    } else {
        return 0; // Button is not pressed
    }
};
int buttonReleased( int button ){
    if (bit_is_set(PINC, button)) { 
        return 1; // Button is released (because pull-up resistor makes it high)
    } else {
        return 0; // Button is still pressed
    }
};
void enableButtonInterrupt(int button) {
    switch (button) {
        case 0:
            EIMSK |= (1 << INT0); // Enable interrupt for INT0
            EICRA |= (1 << ISC01); // Trigger on falling edge (button press)
            break;
        case 1:
            EIMSK |= (1 << INT1); // Enable interrupt for INT1
            EICRA |= (1 << ISC11); // Trigger on falling edge (button press)
            break;
        case 2:
            PCICR |= (1 << PCIE1); // Enable pin change interrupts for group 1
            PCMSK1 |= (1 << PC1); // Enable specific pin for interrupt (adjust as needed)
            break;
        default:
            // Handle other cases if needed
            break;
    }
}

// Enable all button interrupts
void enableAllButtonInterrupts() {
    enableButtonInterrupt(0); // Enable interrupt for button 0
    enableButtonInterrupt(1); // Enable interrupt for button 1
    enableButtonInterrupt(2); // Enable interrupt for button 2
}
