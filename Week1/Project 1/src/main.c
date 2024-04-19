#include <avr/io.h>
int main(){
 DDRB = 0b000000100;
 PORTB = 0b00000000;
 return 0;
}