#include <buttons.h>

void enableButton( int button ){
    DDRC &= ~_BV( button );
    PORTC |= _BV( button ); 
} ;
int buttonPushed( int button ){

};
int buttonReleased( int button ){

};