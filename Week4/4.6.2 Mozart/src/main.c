
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "buzzer.h"
#include "buttons.h"
#include "usart.h"
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <string.h>

#define NOTE_COUNT 10
#define button1 PC1

#define C5  523.250 
#define D5  587.330 
#define E5  659.250 
#define F5  698.460 
#define G5  783.990 
#define A5  880.00 
#define B5  987.770 
#define C6  1046.500 

typedef struct {
    float frequency;
    uint16_t duration;
} NOTE;

typedef struct {
    char* name;
    NOTE** notes;
    uint16_t length;
} SONG;

void playNote (NOTE* note) {
    if (note->frequency == 0) {
       _delay_us(note->duration); // Rest
    } else {
        playTones(note->frequency, note->duration);
    }
}

void PlayTone (float frequency,uint32_t duration){
  uint32_t periodInMicro = (uint32_t)(1000000 / frequency );// Calculate the period in microseconds from the frequency 
}