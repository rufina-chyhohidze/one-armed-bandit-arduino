#include "buzzer.h"

void enableBuzzer() {
    DDRD |= (1 << PD3); // Buzzer is connected to PD3
}


void playTone(float frequency, uint32_t duration) {
    uint32_t periodInMicro = (uint32_t)(1000000 / frequency); // Calculate the period in microseconds from the frequency
    uint32_t durationInMicro = duration * 1000; // We express duration in microseconds
    for (uint32_t time = 0; time < durationInMicro; time += periodInMicro) {
        PORTD &= ~(1 << PD3); // Turn the buzzer on
        _delay_us(periodInMicro / 2); // Wait for the half of the period
        PORTD |= (1 << PD3); // Turn the buzzer off
        _delay_us(periodInMicro / 2); // Wait again for half of the period
    }
}

void disableBuzzer() {
    DDRD &= ~(1 << PD3); // Set PD3 as input to disable the buzzer
}

void playMusic(float *notes, uint32_t *durations, uint8_t numNotes) {
    enableBuzzer(); // Enable the buzzer

    for (uint8_t i = 0; i < numNotes; i++) {
        float frequency = notes[i];
        uint32_t duration = durations[i];
        playTone(frequency, duration); // Play each note with its corresponding duration
        _delay_ms(100); // Add a small delay between notes
    }
}