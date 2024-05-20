#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <display.h>
#include <potentio.h>
#include <buzzer.h>
#include <buttons.h>

volatile uint8_t playing = 0; //  indicate playing state

void initInterrupts() {
    enableAllButtonInterrupts(); // Enable all button interrupts
}

