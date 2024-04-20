#include <util/delay.h>
#include <avr/io.h>

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
void enableMultipleLeds(uint8_t leds){
  for (uint8_t i =0; i<LED_COUNT;i++){
    if (leds & (1<<i)){
      pinMode(i,OUTPUT)
    }
  }
}
void lightUpMultipleLeds(uint8_t leds){
  for (uint8_t i=0;i<LED_COUNT;i++){
    if (leds & (1<<i)){
      digitalWrite(i,LOW) // LOW to turn on LED, HIGH to turn it off
    }
  }
}
void lightDownMultipleLeds(uint8_t leds){
  for(uint8_t i=0;i<LED_COUNT;i++){
    if (leds & (1<<i)){
      digitalWrite(i,HIGH);// HIGH to turn off LED, LOW to turn it on
    }
  }
}
