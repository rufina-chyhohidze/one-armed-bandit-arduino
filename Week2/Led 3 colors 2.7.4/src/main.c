#include <util/delay.h>
#include <avr/io.h>
 #include <avr/interrupt.h> 
 #include <led.h>
 #include <buttons.h>

 #define NB_BUTTONS 3
 int onOff[3]={0,0,0};

 ISR(PCINT1_vect){
  for(int i=0;i<NB_BUTTONS; i++){
    if (buttonPushed(i+1)==1){
      onOff[i]=1 -onOff[i];
    }
  }
 }

 
 int main(){
  enableAllLeds();
  lightDownAllLeds();
  enableAllButtons();
  sei();

  int i;
  while (1){
    for (i=0;i<NB_BUTTONS;i++){
      if (onOff[1]==1){
        lightUpLed(i);
      }
    }
    _delay_ms(100);
    lightDownAllLeds();
    _delay_ms(100);  //whatever led is active, this loop will enable leds flashing ,to activate, we need to use the buttons
  }

 }