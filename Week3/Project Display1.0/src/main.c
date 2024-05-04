#include <util/delay.h> 
#include <avr/io.h> 
#include <usart.h> 
#include <display.h> 

#define NUMBER1 1234
#define NUMBER2 5678
#define NUMBER3 9012

int main() {
    initDisplay(); 
    
    while (1) {
        writeNumber(NUMBER1);
        _delay_ms(1); 
        writeNumber(NUMBER2);
        _delay_ms(1); 
        writeNumber(NUMBER3);
        _delay_ms(1); 
    }

    return 0;
}
