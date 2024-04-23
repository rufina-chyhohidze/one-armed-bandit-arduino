
#include <stdlib.h>  // For rand()
#include <led.h>    // Include the LED header file
#define __DELAY_BACKWARD_COMPATIBLE__  // Allows variables in _delay_ms
#include <util/delay.h>  // For delay functions
#include <avr/io.h>


int main(){
 DDRB = 0b000000100;
 PORTB = 0b00000000;
 return 0;
}