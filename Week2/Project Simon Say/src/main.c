#include <avr/io.h>
#include <avr/interrupt.h>
#include <led.h>
#include <buttons.h>
#include <usart.h>
#include <stdlib.h> 
#include <display.h>

#define PUZZLE_LENGTH 10
#define DELAY_MS 500

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED1 PB2
#define LED2 PB3
#define LED3 PB4
#define LED4 PB5

#define BUTTON1_PIN PC1
#define BUTTON2_PIN PC2
#define BUTTON3_PIN PC3

volatile uint8_t buttonPressed = 0;

void enablePinChangeInterrupt(int pinGroup, int pin) {
    if (pinGroup == 1) { 
        PCICR |= _BV(PCIE1); 
        PCMSK1 |= _BV(pin); 
    }
}

ISR(PCINT1_vect) {
    if (buttonPressed == 0) {
        if (PINC & _BV(PC1)) {
            buttonPressed = 1; 
        }
        else if (PINC & _BV(PC2)) {
            buttonPressed = 2; 
        }
        else if (PINC & _BV(PC3)) {
            buttonPressed = 3; 
        }
    }
}

void ledFlash() {
    LED_DDR |= _BV(LED4);
    while (!buttonPressed) {
        LED_PORT ^= _BV(LED4);
        _delay_ms(DELAY_MS);
    }
    LED_PORT &= ~_BV(LED4); 
}

void generateRandomSeed() {
    uint8_t counter = 0;
    while (!buttonPressed) {
        LED_PORT ^= _BV(LED4);
        _delay_ms(50);
        counter++;
    }
    srand(counter);
}

void generatePuzzle(uint8_t *puzzle, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        puzzle[i] = rand() % 3; 
    }
}

void printPuzzle(uint8_t *puzzle, uint8_t length) {
    printf("[");
    for (uint8_t i = 0; i < length; i++) {
        printf("%d", puzzle[i]);
        if (i < length - 1) {
            printf(" ");
        }
    }
    printf("]\n");
}

void playPuzzle(uint8_t *puzzle, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        switch (puzzle[i]) {
            case 0:
                LED_PORT |= _BV(LED1);
                break;
            case 1:
                LED_PORT |= _BV(LED2);
                break;
            case 2:
                LED_PORT |= _BV(LED3);
                break;
        }
        _delay_ms(DELAY_MS);
        LED_PORT &= ~(_BV(LED1) | _BV(LED2) | _BV(LED3)); 
        _delay_ms(DELAY_MS);
    }
}

int readInput(uint8_t *puzzle, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        if (buttonPressed == puzzle[i]) {
            printf("You pressed button %d, correct!\n", buttonPressed);
        } else {
            printf("You pressed button %d, wrong!\n", buttonPressed);
            printf("Wrong, the correct pattern was: ");
            printPuzzle(puzzle, length);
            return 0; 
        }
        while (buttonPressed);
    }
    printf("Correct, we go to level %d\n", PUZZLE_LENGTH);
    return 1; 
}

int main() {
    DDRB |= _BV(LED1) | _BV(LED2) | _BV(LED3);
    initUSART(); 
    enablePinChangeInterrupt(1, PC1); 
    enablePinChangeInterrupt(1, PC2);
    enablePinChangeInterrupt(1, PC3);
    sei(); 
    
    printf("Press button 1 to start the game\n");
    ledFlash(); // Flash LED until button 1 is pressed

    printf("Generated puzzle: ");
    generateRandomSeed();
    uint8_t puzzle[PUZZLE_LENGTH];
    generatePuzzle(puzzle, PUZZLE_LENGTH);
    printPuzzle(puzzle, PUZZLE_LENGTH);

    playPuzzle(puzzle, PUZZLE_LENGTH); // Play the generated puzzle

    while (1) {
        if (readInput(puzzle, PUZZLE_LENGTH)) {
            break;
        }
    }

    return 0;
}