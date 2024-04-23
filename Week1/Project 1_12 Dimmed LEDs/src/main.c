#include <util/delay.h>
#include <avr/io.h>
#include <led.h> 

#define LED_COUNT 4

int main() {
    
  while (1) {
    // Light up all LEDs for 1 second
    for (int i=0;i<4;i++)
    {
    enabledLed(i);
    lightUpLed(i);
    _delay_ms(3);
    lightDownLed(i);
    _delay_ms(3);
    }
  }
  return 0;
}



