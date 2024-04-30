#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdio.h> 
#include "buttons.h"
#include <led.h>


//all lights up for 2 sec and then countdown pattern is as follows: you first light the 4 LEDs, then 3, 2, 1 and 0 
int main(){
  for(int i=4; i>-1;i--){
    enabledLed(i);
  }
  while (1)
  {
    for (int i=4; i>-1;i--){
      lightUpLed(i);
      _delay_ms(1000);
    }
    for (int i=4; i>-1;i--){
      lightDownLed(i);
      _delay_ms(1000);
    }
    break;
   
  }
  return 0;

}
