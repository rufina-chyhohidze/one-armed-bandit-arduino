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

void dimLed(int ledNumber, int percentage, int duration);

void fadeInLed(int ledNumber, int duration);

void fadeOutLed(int ledNumber, int duration);

//led chaos 
#ifndef LED_H
#define LED_H

#include <Arduino.h>  // Include Arduino functions and constants

#define LED_COUNT 4  // Number of LEDs in your setup

// Initialize the LEDs (set as OUTPUT)
void initLeds();

// Toggle a specific LED with a delay
void toggleLed(int ledNumber, int delayTime);

// Flash a random LED for a random duration
void flashRandomLed();

#endif