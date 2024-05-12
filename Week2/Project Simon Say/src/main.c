#include <avr/io.h>
#include <avr/interrupt.h>
#include <led.h>
#include <buttons.h>
#include <usart.h>
#include <stdlib.h> 


volatile uint8_t ledFlashing = 1; // Enable flashing LED
volatile uint8_t buttonPressed = 0; // Flag to indicate button press
volatile uint8_t counter = 0; // Counter for generating random seed

#define PUZZLE_LENGTH 10 // array of 10
uint8_t puzzle[PUZZLE_LENGTH]; //  store the random puzzle in array
#define DELAY 300

#define LED1 PB2
#define LED2 PB3
#define LED3 PB3

void enablePinChangeInterrupt(int pinGroup, int pin) {
    if (pinGroup == 1) { 
        PCICR |= _BV(PCIE1); 
        PCMSK1 |= _BV(pin); 
    }
}

ISR(PCINT1_vect) {
    if (buttonPressed == 0 && (PINC & _BV(PC1))) {
        buttonPressed = 1; 
    }
}

// generate the random puzzle
void generatePuzzle(uint8_t *puzzle, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        puzzle[i] = rand() % 3; 
    }
}

// prints the puzzle array to Serial Monitor
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

void playPuzzle(uint8_t *puzzle,uint8_t length){
  for (uint8_t i =0; i<length;i++){
    switch (puzzle[i])
    {
    case 0:
      lightUpLed(LED1);
      break;
    case 1:
     lightUpLed(LED2);
     break;
    case 2:
     lightUpLed(LED3);
     break;
      default:
      break;
    }
    _delay_ms(DELAY);
    lightDownAllLeds (); //turn off all leds
  }

}

int main() 
{ 
  
    initUSART(); 
    DDRB |= _BV(PB5); 
    enablePinChangeInterrupt(1, PC1); 
    
    sei(); 
    
    while (1) 
    {
        if (ledFlashing) {
            PORTB ^= _BV(PB5); 
            _delay_ms(DELAY);
            counter++; 
        }
        
        if (buttonPressed) {  
            srand(counter);
            generatePuzzle(puzzle, PUZZLE_LENGTH);
            
            printf("Random Puzzle: ");
            printPuzzle(puzzle, PUZZLE_LENGTH);

             playPuzzle(puzzle, PUZZLE_LENGTH);
            
            buttonPressed = 0; 
        }
    }
    return 0; 
}