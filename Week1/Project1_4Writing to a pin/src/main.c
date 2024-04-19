#include <avr/io.h>
#include<util/delay.h>

int main(){
  DDRB=0b00010000;
  while(1){
    PORTB=0b00000000;
    _delay_ms(500);
    PORTB=0b00010000;
    _delay_ms(500);
  }
  return 0;
}
/*
The 3rd led is connected to PB4, numbered from right to left (start counting from 0)
 //A while 1 loop to blink "forever" 
  //we don't apply voltage to PB4, so there is a voltage difference, by consequence the led lights up
  //we apply voltage to PB4, so the voltage difference becomes 0, by consequence the led goes dark

*/