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