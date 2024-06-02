//at first including each library,that i will use in this project.
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <potentio.h>
#include <led.h>
#include <buttons.h>
#include <buzzer.h>
#include <display.h>
#include <usart.h>  
#include <string.h>
#include <time.h>
 
//defining leds,buttons,buzzer...
#define LED1 PB2
#define LED2 PB3
#define LED3 PB4
#define LED4 PB5
#define BUZZER_PIN PD3
 
#define BUTTON1 PC1
#define BUTTON2 PC2
#define BUTTON3 PC3
 
//using macro's to express the constant values
#define START_COINS 10 //i decreased start coins, to play faster for a moment.
#define MAX_COINS 10
#define WIN_AMOUNT_2 5
#define WIN_AMOUNT_3 50
#define WIN_AMOUNT_4 500
 
//DEFINING NOTES
#define C4  261.63
#define D4  293.66
#define E4  329.63
#define F4  349.23
#define G4  392.00
#define A4  440.00
#define B4  493.88
#define C5  523.25
#define D5  587.33
#define E5  659.25
#define F5  698.46
#define G5  783.99

#define DURATION 150 //defining duration for note
//#define MAX_GAME_STATES 10
 
int coins = START_COINS;
volatile unsigned long gameTimeSeconds = 0;
 
typedef struct {
    int sequence;
    int coins;
    int wager;
    int *displayValues;
    int winAmount;
} GameState;

GameState* initGameState(int slotCount) {
    GameState *state = (GameState *)malloc(sizeof(GameState));
    if (state == NULL) {
        // handling memory allocation failure
        printf("Memory allocation failed\n");
        exit(1);
    }
    state->coins = START_COINS; // initialize coins to START_COINS
    // Allocate memory for the display values array
    state->displayValues = (int *)malloc(slotCount * sizeof(int));
    if (state->displayValues == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
        free(state); // Free previously allocated memory
        exit(1);
    }
    // initialize displayValues array elements to 0
    for (int i = 0; i < slotCount; i++) {
        state->displayValues[i] = 0;
    }
    return state;
}
void freeGameState(GameState *state) {
    if (state != NULL) { //if state not equals 0 --->
        free(state->displayValues);// free memory allocated for the display values array
        free(state); //free memory allocated for the game state structure
    }
}
 
void initTimer() {
    TCCR0B |= (1 << CS02) | (1 << CS00); // sets prescaler 1024, (1024 / 16,000,000) seconds,a 16 MHz clock frequency.
    TIMSK0 |= (1 << TOIE0); // enable overflow interrupt
    sei();
}
/*Timer 0 will count up from 0 to its maximum value
(255 for an 8-bit timer)
  and then overflow back to 0.
Each time it overflows, this ISR is triggered*/
ISR(TIMER0_OVF_vect) {
    gameTimeSeconds++;
}
 
//function to dsiplay calculated gameTimeSeconds in serial monitor.
void displayGameTime() {

    int seconds = gameTimeSeconds / 60;
    printf("\nTotal game time: %d seconds\n", seconds);
 
}
 
void victorySound() {
 
  float frequencies [] = {C4, E4, G4, C5, C5, G4, E4, C4, G4, A4, B4, C5, G4, E4, D4, C4}; //array with C D E C twice, followed by E F G once
  enableBuzzer (); 
  for ( int  note = 0 ; note < 8 ; note ++ ) { //go through each note in array
  playTones ( frequencies [ note ], DURATION ); //play current note, with defined duration of 150 ms
  _delay_ms( 50 ); //wait 50 ms between the notes
  }
 
}
 
void lossSound() {
    float frequencies[] = {C5, B4, A4, G4, F4, E4, D4, C4}; //array for descending pattern for loss sound
    int numNotes = sizeof(frequencies) / sizeof(frequencies[0]); //calculate the number of notes in array
    enableBuzzer();
    for (int note = 0; note < numNotes; note++) { //loop through each note in array
        playTones(frequencies[note], DURATION); //play the current note with defined duration of 150 ms
        _delay_ms(50); // Wait 50 ms between the notes
    }
}
  
// Function to print rules of the game to the serial monitor,used 200ms of delay for better readability.
void printGameRules() {
    printf("\nPlace your bet: Press the right button once to bet 1 coin per turn. LED displays light up, and a sound signifies the bet.\r\n");
    _delay_ms(200);
    printf("\nActivate the slot machine: Press the right button again to start the game. Watch as random numbers appear and jump on the displays.\r\n");
    _delay_ms(200);
    printf("\nWin big: If all displays show the same number, hear the victory sound and win coins! Win 5 for 2 displays, 50 for 3, or 500 for 4.\r\n");
    _delay_ms(200);
    printf("\nGame over: Lose all your coins, and the game stops with a loss message. Reach 9999 coins, and the game ends with a \"bank break\" message.\r\n");
     printf("\n----------Choose your game: Select a 2, 3, or 4 display slot machine.---------------------\r\n");
     printf("                        PRESS BUTTON 1 FOR 2 SLOTS DISPLAY.\n");
    _delay_ms(200);
    printf("                        PRESS BUTTON 2 FOR 3 SLOTS DISPLAY.\n");
    _delay_ms(200);
    printf("                        PRESS BUTTON 3 FOR 4 SLOTS DISPLAY.\n");
 
}
 
//function for display coins on serail monitor and display
void displayCoins(int coins) {
 
    char coinsStr[5]; //store the coin count as a string.
    snprintf(coinsStr, sizeof(coinsStr), "%4d", coins);//convert the integer coin count to a string with a width of 4 characters
 
    for(int i = 0; i < 4; i++) { //loop through each character in a string
        writeCharToSegment(i, coinsStr[i]); //write each char to corresponding segment
    }
}
 
//function to generate the random number and show it on the display
void displayRandomNumbers(GameState *state, int slotCount) {
    printf("Generating random numbers...\n"); //prints generated numbers 
    
    for (int i = 0; i < slotCount; i++) {
        state->displayValues[i] = rand() % 10; // Generate random number between 0 and 9 for each slot
    }
    // Debug print statement to show the generated numbers
    printf("Generated numbers: ");
    for (int i = 0; i < slotCount; i++) {
        printf("%d ", state->displayValues[i]);
    }
    printf("\n");
    
    // Display each number on the LED display with a delay between each display
    for (int i = 0; i < slotCount; i++) {
        writeNumberToSegment(i, state->displayValues[i]); // Write the number to the corresponding segment
        _delay_ms(800); // it holds 800 ms the number on display
    }
   

    // Check if all numbers are the same
    int win = 1; // Flag if all numbers are the same
    for (int i = 1; i < slotCount; i++) { 
        if (state->displayValues[i] != state->displayValues[0]) { // Compare each number with the first number
            win = 0; // If any number is different, set the flag to 0
            break; // Exit the loop as we found a mismatch
        }
    }
    if (win) { // If win is still 1, all numbers are the same 
        // Determine the amount of win based on the number of slots
        int winAmount = (slotCount == 2) ? WIN_AMOUNT_2 : (slotCount == 3) ? WIN_AMOUNT_3 : WIN_AMOUNT_4;
        state->coins += winAmount; // Add the win amount to the player's coins
        printf("Congratulations! You won %d coins!\n", winAmount);
    }

    // Update coin display
    displayCoins(state->coins);
}
//function to chech if the game is over
void checkGameOver(GameState *state) {
    if (state->coins <= 0) { //if player's amount of coind less than 0, print loss statement 
        printf("Game over! You have run out of coins.\n");
        lossSound();
        _delay_ms(2000);
        printf("Press the RESTART button to try your luck again!");
         displayGameTime(); // Display total game time
        while (1) {
            //place for displaying loss
            writeCharToSegment(0,'l');
            writeCharToSegment(1,'o');
            writeCharToSegment(2,'s');
            writeCharToSegment(3,'s');
        }
    } else if (state->coins >= MAX_COINS) { //if player's coins reached max coins number, print win statement.
        printf("Congratulations! Bank break! You have reached the maximum coins.\n");
        _delay_ms(1000);
        printf("Press the RESTART button to try your luck again!");
         displayGameTime(); // display total playing time in seconds in the end of the game.
        victorySound(); //play sound of victory
        while (1) {
           //shows winning 7777!!!
            writeNumber(7777);
           
           
        }
    }
}
 
void checkWin(GameState *state, int slotCount) {
    int winAmount = 0; //variable to store winning amount 
    int sameNumber = 1; // Flag to check if all numbers are the same
    int targetNumber = state->displayValues[0]; // Store the first number as the target number
 
    // Checks if all numbers are the same
    for (int i = 1; i < slotCount; i++) { //loop through remaining numbers 
        if (state->displayValues[i] != targetNumber) { //if any number is diff from the target number
            sameNumber = 0; // Set the flag to false then
            break; //exit loop bc we have false.
        }
    }
 
    if (sameNumber) { // If all numbers are the same
        winAmount = (slotCount == 2) ? WIN_AMOUNT_2 : (slotCount == 3) ? WIN_AMOUNT_3 : WIN_AMOUNT_4; //if slotCount ==2 true, assign win_amount_2 to winAmount,if false assign win_amount_3 and if it's false assign win_amount_4.
        state->coins += winAmount; // Add the win amount to coins
        printf("Congratulations! You won %d coins!\n", winAmount);
    } else {
        printf("Better luck next time!\n");
    }
 
    displayCoins(state->coins); // Update coin display
}


int main() {
    // Initialization
    initADC();//initialise potentio
    initUSART(); // communication with my PC over the serial port (USB cable).
    initDisplay();//initialise display
    initTimer(); //enables timer routine and ISR
    int value = potentioMeterNumber(); //read value from potentio,and use it for random generated numbers.
    srand(value); ////read value from potentio,and use it for random generated numbers.
    writeWelcomeToTheUserOnDisplay(); // running lines of welcoming (in display.c)
    //DDRB |= _BV(PB2);
   
    // Print game rules
    printf("----------------------------WELCOME TO ONE ARMED BANDIT!----------------\n ");
    _delay_ms(900);
    printf("-----------------------------------------------------------------------\n ");
    _delay_ms(900);
    printf("---$_$_$_$_$_$_$_$_$_$_$_$_$_$ RULES TO PLAY: _$_$_$_$_$_$_$_$_$_$_$_$_$_$---\n ");
    _delay_ms(900);
    printGameRules();

        GameState *state = initGameState(4); // Initialize game state for 4 slots (max slot count)

    
    while (1) {       
        if (bit_is_clear(PINC, BUTTON1)) {
            printf("Your choice is: 2 slots display.\n");
            //makeBet();
            state->coins--;
            //coins-= bet; // substract one coin for the bet
            displayCoins(state->coins); // Update coin display
            printf("We are starting the game! Your current bank is: %d coins\n", state->coins);
            rollOnDisplay(); //imitates the roll
           
           
 
            //this loop makes 2 leds blinks twice,and then it generate numbers.
            for(int i=0;i<2;i++){
            lightUpMultipleLeds(0b0011); //set 2 leds on
            _delay_ms(200);
            lightDownAllLeds();
            _delay_ms(200);
           
            }
 
            // Generate and display random numbers for 2 slots(theyre always be different with use of potentio)
            displayRandomNumbers(state, 2);
            checkWin(state, 2); // checks for win state, 2 same numbers in a ROW!
            checkGameOver(state); // it checks if the game is over
 
        } else if (bit_is_clear(PINC, BUTTON2)) {
 
            //similar pattern for 3 slots
            printf("Your choice is: 3 slots display.\n");
            state->coins--; // substract one coin for the bet
            displayCoins(state->coins); // Update coin display
            printf("We are starting the game! Your current bank is: %d coins\n", state->coins);
            rollOnDisplay();
             
            //this loop blink 3 leds 3 times
            for(int i = 0; i < 3; i++){
 
            lightUpMultipleLeds(0b0111);//set 3 leds on
            _delay_ms(150);
            lightDownAllLeds();
            _delay_ms(150);//waits 150ms 
 
            }
 
            // Generate and display random numbers for 3 slots(theyre always be different with use of potentio)
             displayRandomNumbers(state, 3); // Generate and display random numbers for 3 slots
            checkWin(state, 3);// 3 same numbers in a ROW!
            checkGameOver(state);  
       
 
        } else if (bit_is_clear(PINC, BUTTON3)) {
            printf("Your choice is: 4 slots display.\n");
            state->coins--; // substract one coin for the bet
            displayCoins(state->coins); // Update coin display
            printf("We are starting the game! Your current bank is: %d coins\n", state->coins);
            rollOnDisplay(); //shows the animation of roll on display
 
            //this loop blink 4 leds 4 times
            for (int i=0;i<4;i++){
            lightUpMultipleLeds(0b1111); //set 4 leds on
            _delay_ms(150);
            lightDownAllLeds();
            _delay_ms(150);
            }
 
            // Generate and display random numbers for 4 slots(theyre always be different with use of potentio)
             displayRandomNumbers(state, 4); // Generate and display random numbers for 3 slots
            checkWin(state, 4);// 4 same numbers in a ROW!
            checkGameOver(state);  
        }
        writeNumber(state->coins);
    }
    freeGameState(state); // Free the dynamically allocated memory before exiting
    return 0;
 
}