#include <util/delay.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__  

#define __DELAY_BACKWARD_COMPATIBLE__    

#include <stdlib.h>
#include "led.h"


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
DDRB |= (leds<<2);
}
  
void lightUpMultipleLeds(uint8_t leds) {
  enableMultipleLeds(leds);
  PORTB &=~(leds<<2);
}

void lightDownMultipleLeds(uint8_t leds) {
  enableMultipleLeds(leds);
  PORTB&=~(leds<<2);

}
void enableAllLeds() {
    for (int i = 0; i < LED_COUNT; ++i) {
        enableOneLed(i); // Enable each LED one by one
    }
}
#define MIN_LED_NUMBER 0
void lightUpOneLed(int led) {
    if (led >= MIN_LED_NUMBER && led < LED_COUNT) { // Check if led number is within the valid range
        PORTB &= ~(1 << (PB2 + led)); // Turn on the specified LED
    }
}
void lightUpAllLeds() {
    for (int i = 0; i < LED_COUNT; ++i) {
        lightUpOneLed(i); // Turn on all LEDs
    }
}
/*
void lightUpAllLeds(){
  enableAllLeds();
  PORTB&=~(1<<(PB2+0));
  PORTB&=~(1<<(PB2+1));
  PORTB&=~(1<<(PB2+3));
   PORTB&=~(1<<(PB2+4));
}
*/




//Dimmed leds
/*#define NUMBER_OF_LEDS 4

void dimLed(int ledNumber, int percentage, int duration) {
  if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS) {
    return;  // Ensure the LED number is valid
  }
  int onTime = (percentage * duration) / 100;
  int offTime = duration - onTime;

  pinMode(ledNumber, OUTPUT);  // Set the pin mode to output

  while (1) {
    digitalWrite(ledNumber, LOW);  // LED off
    _delay_ms(offTime);            // Delay for off time
    digitalWrite(ledNumber, HIGH);  // LED on
    _delay_ms(onTime);              // Delay for on time
  }
}

void fadeInLed(int ledNumber, int duration) {
  dimLed(ledNumber, 100, duration);  // Fully on during fade-in
}

void fadeOutLed(int ledNumber, int duration) {
  dimLed(ledNumber, 0, duration);  // Fully off during fade-out
}
*/
/*
//LED chaos
void initLeds() {
    // Set all LEDs as OUTPUT and turn them off
    for (int i = 0; i < LED_COUNT; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);  // Ensure LEDs start off
    }
}

void toggleLed(int ledNumber, int delayTime) {
    if (ledNumber >= 0 && ledNumber < LED_COUNT) {
        // Toggle the LED on and off with a specific delay
        digitalWrite(ledNumber, HIGH);  // Turn on the LED
        _delay_ms(delayTime);           // Delay
        digitalWrite(ledNumber, LOW);   // Turn off the LED
    }
}

void flashRandomLed() {
    // Generate a random LED index and delay time
    int led = rand() % LED_COUNT;  // Random LED index
    int delayTime = 100 + (rand() % 901);  // Delay between 100 and 1000 ms

    toggleLed(led, delayTime);  // Flash the random LED

    // Random delay before the next flash
    delayTime = 100 + (rand() % 901);
    _delay_ms(delayTime);  // Pause before the next flash
}
*/


