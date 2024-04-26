#include <stdio.h>
#include <usart.h>
#include <avr/io.h>
#include <util/delay.h>

void enableButton( int button ); 
int buttonPushed( int button ); 
int buttonReleased( int button );

