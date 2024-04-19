#include <util/delay.h>//This library includes the function named _delay_ms(..) which pauses the execution of the program.
#include <avr/io.h>//Use this library to name the various registers of the ATmega328P microcontroller, like eg DDRB

int main(){
  //DDRB=0b00100000;//Write a binary number to the Data Direction Register B. Pin 5 of port B is enabled for writing with this setting.
  DDRB |=(1<<5);//<< bitshift operator.
  while (1){
    PORTB=(0<<(PB2+3));//We write a 0 to PB2+3 to let the connected LED light up.
    _delay_ms(500);
    PORTB=(1<<(PB2+3)); //We write a 1 to PB2+3 to let the connected LED go dark.
    _delay_ms(1500);
  }
  return 0;
}