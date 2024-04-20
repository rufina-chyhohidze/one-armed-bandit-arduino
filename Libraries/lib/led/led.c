#include <util/delay.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__  
#include <util/delay.h> 


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
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    if (leds & (1 << i)) {
      pinMode(i, OUTPUT);
    }
  }
}

void lightUpMultipleLeds(uint8_t leds) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    if (leds & (1 << i)) {
      digitalWrite(i, LOW); // LOW to turn on LED, HIGH to turn it off
    }
  }
}

void lightDownMultipleLeds(uint8_t leds) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    if (leds & (1 << i)) {
      digitalWrite(i, HIGH); // HIGH to turn off LED, LOW to turn it on
    }
  }
}

void dimLed(int ledNumber, int percentage, int duration) {
  if (ledNumber < 0 || ledNumber > NUMBER_OF_LEDS - 1) return;
  int onTime = (percentage * duration) / 100;
  int offTime = duration - onTime;
  pinMode(ledNumber, OUTPUT);
  
  while (1) {
    digitalWrite(ledNumber, LOW);
    _delay_ms(offTime);
    digitalWrite(ledNumber, HIGH);
    _delay_ms(onTime);
  }
}

void fadeInLed(int ledNumber, int duration) {
  dimLed(ledNumber, 100, duration);
}

void fadeOutLed(int ledNumber, int duration) {
  dimLed(ledNumber, 0, duration);
}
