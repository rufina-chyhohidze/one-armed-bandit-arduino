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


#define __DELAY_BACKWARD_COMPATIBLE__  
#include <util/delay.h> 

void dimLed(int ledNumber, int percentage, int duration);

void fadeInLed(int ledNumber, int duration);

void fadeOutLed(int ledNumber, int duration);