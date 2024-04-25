
#include <stdlib.h>  // For rand()
#include <time.h>
#include <led.h>    
#include <util/delay.h>  
#include <avr/io.h>

#define NUMBER_OF_LEDS 4
int main(){
    srand((unsigned)time(NULL)); // NULL for current time
    while (1) {
     for (int i=1;i<4;i++)
    {
    enabledLed(i);
    lightDownLed(i);
    _delay_ms(100);
  }
    for (int i=2;i<4;i++)
    {
    enabledLed(i);
    lightUpLed(i);
    _delay_ms(100);
    lightDownLed(i);
    _delay_ms(100);
  }
  for (int i=4;i<20;i++)
    {
    enabledLed(i);
    lightUpLed(i);
    _delay_ms(100);
    lightDownLed(i);
    _delay_ms(100);
  }
   for (int i=3;i<4;i++)
    {
    enabledLed(i);
    lightUpLed(i);
    _delay_ms(100);
    lightDownLed(i);
    _delay_ms(100);
    }
    for (int i=0;i<2;i++)
    {
    enabledLed(i);
    lightUpLed(i);
    _delay_ms(100);
    lightDownLed(i);
    _delay_ms(100);
    }
    for (int i=0;i<4;i++)
    {
    enabledLed(i);
    lightUpLed(i);
    _delay_ms(100);
    lightDownLed(i);
    _delay_ms(100);
    }
  return 0;
}
    }

