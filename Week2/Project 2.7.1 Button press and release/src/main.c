#include <util/delay.h> 
#include <avr/io.h> 
#include <usart.h> 
#include<buttons.h>

#include <avr/io.h> 
#include <util/delay.h> 
#include <usart.h> 
#include <buttons.h> 

int main() 
{ 
    //reacts on push the buttons (PC1-PC3)and LED'S(PB2-PB4).
    initUSART(); 
    enableButton(PC1); 
    enableButton(PC2); 
    enableButton(PC3); 
    DDRB |= _BV(PB2); //controlling an LED
    DDRB |= _BV(PB3);
    DDRB |= _BV(PB4);

    while (1) 
    {
        if (buttonPushed(PC1)) {
            PORTB |= _BV(PB2); // Turn on LED
            printf("LED turned on!\n");
        } else {
            PORTB &= ~_BV(PB2); // Turn off LED
            printf("LED turned off.\n");
        }
        _delay_ms(1000); 
        if (buttonPushed(PC2)){
        PORTB|= _BV(PB3);
        printf("LED 2 turned on!\n");
    }else {
        PORTB&=~_BV(PB3);
        printf("LED 2 turned off.\n");
    }
    _delay_ms(1000);
    if(buttonPushed(PC3)){
        PORTB|=_BV(PB4);//Turn on LED 3
        printf("LED 3 turned on!\n");
    }else{
        PORTB&=~_BV(PB4);
        printf("LED 3 turned off.\n");
    }
    _delay_ms(1000);
    }

    return 0; 
}
/*int main() 
{ 
  
    initUSART(); 
    // Enable button 1 (which is on PC1)
    enableButton(PC1); 

    while (1) 
    {  
        if (buttonPushed(PC1)==1) {
            printf(" - Button 1 pressed!\n"); 
           
        } else { 
            printf(" - Button 1 NOT pressed!!\n"); 
        }
        _delay_ms(1000); 
        if (buttonReleased(PC1)==1) { // Check if button on PC1 is released
            printf("Button on PC1 is released!\n");
        } else {
            printf("Button on PC1 is still pressed.\n");
        break;
        }
        _delay_ms(1000); 
    }
    return 0;
}
*/
/* //two buttons reads input 
int main() 
{ 
    initUSART(); 
    enableButton(PC1); 
    enableButton(PC2); // Enable a second button

    while (1) 
    {
        if (buttonPushed(PC1)) {
            printf("Button on PC1 is pressed!\n");
        }

        if (buttonPushed(PC2)) {
            printf("Button on PC2 is pressed!\n");
        }

        _delay_ms(1000); 
    }

    return 0; 
}
*/