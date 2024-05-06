#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include "buttons.h"

#define button1 PC1
#define button2 PC2
#define button3 PC3
int main() {
    initDisplay();
    enableAllButtons(); 
    
    while (1) {
        int button1State = buttonPushed(button1); // Read button 1 state
        int button2State = buttonPushed(button2); // Read button 2 state
        int button3State = buttonPushed(button3); // Read button 3 state

        //I CREATED A 4 numbers representation for checking the state of the button

        // Using binary-like representation (e.g., 0110 for 2nd and 3rd buttons pressed)
        int displayValue = 1000 * button1State + 100 * button2State + 10 * button3State;

        writeNumber(displayValue); 
          
        /*when you press the button1 - 3,
        the number 1 appears on display according to
        the 1-3 number (1st button-1st number) */

        _delay_ms(0.100); 
    }

    return 0; 
}