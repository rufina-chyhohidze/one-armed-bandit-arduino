#include <buttons.h>

void enableButton( int button ){
    DDRC &= ~_BV( button );
    PORTC |= _BV( button ); 
} ;
int buttonPushed( int button ){
    if (bit_is_clear(PINC, button)) { // Assuming buttons are connected to Port C
        return 1; // Button is pressed (because pull-up resistor makes it high when not pressed)
    } else {
        return 0; // Button is not pressed
    }
};
int buttonReleased( int button ){

};