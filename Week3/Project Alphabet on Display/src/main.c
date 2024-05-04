#include <avr/io.h>
#include <util/delay.h>
#include "display.h"

int main() {
    initDisplay(); 

    while (1) {
        writeString("HELLO"); //ACTUALLY LIFE GIVES ME SIGNS AND PRINT HELL INSTEAD LMAO
        _delay_ms(0.100); // Hold the display for 2 secondss
    }
    return 0;
}