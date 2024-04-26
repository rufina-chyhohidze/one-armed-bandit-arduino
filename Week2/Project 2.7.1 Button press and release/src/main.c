#include <util/delay.h> 
#include <avr/io.h> 
#include <usart.h> 
#include<buttons.h>


int main() 
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
    } 
    return 0; 
}