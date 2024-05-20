#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>
#include <avr/interrupt.h>

void initTimer0()
{
    // STEP 1: choose the WAVE FORM and by consequence the Mode of Operation
    // We choose FAST PWM; TCNT0 counts to 255
    TCCR0A |= _BV(WGM00) | _BV(WGM01); // WGM00 = 1 and WGM01 = 1 --> Fast PWM Mode

    // STEP 2: *always* set a PRESCALER, otherwise the timer won't count
    // The counting speed is determined by the CPU clock (16 Mhz) divided by this factor
    TCCR0B |= _BV(CS01) | _BV(CS00); // CS00 and CS01 = 1 --> prescaler, factor is now 64
    // STEP 3: enable INTERRUPTS
    // Enable interrupts for overflow: TCNT0 == TOP
    TIMSK0 |= _BV(TOIE0); // enable overflow interrupt
}

volatile int countdown = 10;
volatile int doneFlashing = 0;
volatile int displayState = 0; // 0 for countdown, 1 for DONE flashing

// This ISR runs every time TCNT0 equals the TOP value (255)
ISR(TIMER0_OVF_vect)
{
    if (displayState == 0)
    {
        writeNumber(countdown);
        blankSegment(3); // Otherwise the last segment is much brighter than the rest
    }
    else
    {
        if (doneFlashing % 2 == 0)
        {
            writeString("ALOR");
        }
        else
        {
            clearDisplay();
        }
        doneFlashing++;
    }
}

int main()
{
    initUSART();
    initDisplay();
    initTimer0(); // initialize Timer 0
    sei(); // enable interrupts globally

    while (1)
    {
        if (displayState == 0)
        {
            for (int i = countdown; i >= 0; i--)
            {
                countdown = i;
                _delay_ms(1000);
            }
            displayState = 1; // Switch to DONE flashing state
            doneFlashing = 0; // Reset the flashing counter
        }
        else
        {
            // Flash "DONE" for 10 seconds
            for (int i = 0; i < 10; i++)
            {
                _delay_ms(1000);
            }
            // Reset for another countdown
            countdown = 10;
            displayState = 0;
        }
    }
    return 0;
}