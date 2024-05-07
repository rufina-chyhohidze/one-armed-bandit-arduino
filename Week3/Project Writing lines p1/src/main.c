#include <avr/io.h>
#include <util/delay.h>
#include "buttons.h"
#include "usart.h"
#include <display.h>

#define button1 PC1 

int main() {
    initDisplay();
    initUSART();
    enableAllButtons();
    
    int displayValue=0;

    while (1) {
        if (buttonPushed(button1)) {
          buttonPushed(button1); //additional it shows 1 on the screen when the button is pressed.
          displayValue+=1;
          writeNumber(displayValue); 
          
          _delay_ms(0.100);
            for (int i = 1; i <= 100; i++) {
                printf("%d: I am not allowed to speak in class.\n", i);
                _delay_ms(100); 
            }
            // After sending 100 messages, break the loop
            break;
        }
        _delay_ms(50);
    }

    return 0; 
};