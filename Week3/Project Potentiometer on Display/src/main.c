#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>

void initADC()
{
    ADMUX |= (1 << REFS0); // Set up the reference voltage. We choose 5V as the reference. 
    ADMUX &= ~(1 << MUX3 ) & ~(1 << MUX2 ) & ~(1 << MUX1 ) & ~(1 << MUX0 ); 
                                                          //Set MUX0-3 to zero to read analog input from PC0 
                                                          //Default is 0000 so this setting is not really necessary      
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Determine the sample rate by setting the division factor to 128.
    ADCSRA |= (1 << ADEN); // Enable the ADC
    ADCSRA |= (1 << ADATE); // Enable ADC Auto Triggering
    ADCSRB = 0; // Set ADC Auto Trigger Source to Free Running Mode (default)
    ADCSRA |= (1 << ADSC); // Start the analog-to-digital conversion
}

int main()
{
    initUSART();
    initADC();
    initDisplay(); // Initialize the display
  
    while (1)
    {
        
        uint16_t adcValue = ADC; 
        int displayValue = (adcValue * 10000) / 1024; // Scale to 4-digit number
        writeNumber(displayValue); 

        printf("Value: %d\n", adcValue);
        _delay_ms(0.100); // Delay for better readability, adjust as needed
    }

    return 0;
}

