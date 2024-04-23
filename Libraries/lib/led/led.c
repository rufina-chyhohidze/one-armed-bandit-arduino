#include <util/delay.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__  
#include <stdlib.h>
#include <led.h>


#define NUMBER_OF_LEDS 4 //Define is a "preprocessor directive". It ensures that every NUMBER_OF_LEDS will be replaced by 4 in the following code

void enabledLed(int lednumber)//C has no classes; functions can be included directly in the .c file.
{
  if (lednumber <0 || lednumber>NUMBER_OF_LEDS-1)return;
  DDRB |=(1<<(PB2+lednumber));
}
void lightUpLed ( int lednumber )    //Note: enabled LEDs light up immediately ( 0 = on )
{
  if (lednumber<0||lednumber>NUMBER_OF_LEDS-1)return;
  PORTB &=~(1<<(PB2+lednumber));
}
void lightDownLed ( int lednumber )
{
  if(lednumber<0||lednumber>3)return;
  PORTB |=(1<<(PB2+lednumber));
}
#define LED_COUNT 4
void enableMultipleLeds(uint8_t leds) {
DDRB |= (leds<<2)
}
  
void lightUpMultipleLeds(uint8_t leds) {
  enableMultipleLeds(leds)
  PORTB &=~(leds<<2)
}

void lightDownMultipleLeds(uint8_t leds) {
  enableMultipleLeds(leds)
  PORTB&=~(leds<<2)

}
/*
void lightUpAllLeds(){
  enableAllLeds();
  PORTB&=~(1<<(PB2+0));
  PORTB&=~(1<<(PB2*1));
  PORTB&=~(1<<(PB2*3));

}
*/



