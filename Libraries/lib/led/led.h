
#include <stdio.h>
#include <avr/io.h>

void enabledLed(int);

void enableMultipleLeds(uint8_t leds); 

void enableAllLeds ();

void lightUpLed(int); 

void lightUpMultipleLeds (uint8_t leds);

void lightUpAllLeds (); 

void lightDownLed(int); 

void lightDownMultipleLeds (uint8_t leds);

void lightDownAllLeds (); 

void lightToggleOneLed(int);


void fadeInLed(int, long);

void fadeOutLed(int, long);

/* Dims the LEDs the specified percentage, during the specified amount of time (lednumber, dimming %, duration in ms) */
void dimLed(int, int, long);


