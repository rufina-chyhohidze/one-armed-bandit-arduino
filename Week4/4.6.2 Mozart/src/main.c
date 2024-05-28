
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "buzzer.h"
#include "buttons.h"
#include "usart.h"
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