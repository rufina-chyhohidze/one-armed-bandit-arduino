
#include <avr/io.h>
#include <util/delay.h>
#ifndef buzzer.h
#define buzzer.h

void enableBuzzer();
void disableBuzzer();
void playTone(float frequency, uint32_t duration);
void playMusic(float *notes, uint32_t *durations, uint8_t numNotes);

#endif