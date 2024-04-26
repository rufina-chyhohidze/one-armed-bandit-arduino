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
            break;
        } else { 
            printf(" - Button 1 NOT pressed!!\n"); 
      
        }
        _delay_ms(1000); 
        if (buttonReleased(PC1)==1) { // Check if button on PC1 is released
            printf("Button on PC1 is released!\n");
        } else {
            printf("Button on PC1 is still pressed.\n");
        
        }
        _delay_ms(1000); 
    }
    return 0; 
}