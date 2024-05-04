#include <avr/io.h>
#include <util/delay.h>
#include "display.h"

int main() {
    initDisplay(); // Initialize the display

    while (1) {
        // Display a test string using writeString
        writeString("OPEN");
        _delay_ms(2000); // Hold the display for 2 seconds

        // Display a different string
        writeString("AIRO");
        _delay_ms(2000); // Hold the display for 2 seconds
    }

    return 0;
}