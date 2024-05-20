#include <avr/io.h>
#include <util/delay.h>

// Define buzzer pin
#define BUZZER_PIN PD3

// Function to play a note with given frequency and duration
void playNote(uint16_t frequency, uint32_t duration_ms) {
    // Calculate period
    uint32_t period_us = 1000000UL / frequency;

    // Calculate number of cycles based on duration
    uint32_t num_cycles = duration_ms * 1000UL / (period_us * 2);

    // Loop for the duration of the note
    for (uint32_t i = 0; i < num_cycles; i++) {
        // Turn on buzzer
        PORTD |= (1 << BUZZER_PIN);
        _delay_us(period_us / 2);
        // Turn off buzzer
        PORTD &= ~(1 << BUZZER_PIN);
        _delay_us(period_us / 2);
    }
}

int main() {
    DDRD |= (1 << BUZZER_PIN);
    playNote(880, 5000); 
    return 0;
}