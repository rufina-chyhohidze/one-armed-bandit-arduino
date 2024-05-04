#include <avr/io.h>
#include <util/delay.h>
#include "display.h"


int main() {
    int startNumber = 1234; 
    int currentNumber = startNumber; // Keep track of the current number
    initDisplay(); 
    while (1) {
       //writeNumber( startNumber); // Display the 1234 number
       writeNumber( currentNumber);
        _delay_ms(0.100); 
        currentNumber = (currentNumber + 1) % 10000; // Increment and wrap at 9999
    }
    return 0; 
}
