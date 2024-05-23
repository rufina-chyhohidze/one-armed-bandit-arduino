//at first including each library,that i will use in this project.
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

//defining leds,buttons...
#define LED1 PB2
#define LED2 PB3
#define LED3 PB4
#define LED4 PB5
#define BUZZER_PIN PD3

#define BUTTON1 PC1
#define BUTTON2 PC2
#define BUTTON3 PC3

//using macro's to express the constant values 
#define START_COINS 50
#define MAX_COINS 9999
#define WIN_AMOUNT_2 5
#define WIN_AMOUNT_3 50
#define WIN_AMOUNT_4 500

#define MAX_GAME_STATES 10
int coins = START_COINS;

typedef struct {
    int sequence;
    int coins;
    int wager;
    int displayValues[4];
    int winAmount;
} GameState;

const int ledPins[] = {LED1, LED2, LED3, LED4};
const int buttonPins[] = {BUTTON1, BUTTON2, BUTTON3};

void initGame() {
    // I plan to initialize LEDs, buttons, etc. in this function
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
    char coinsStr[5];
    snprintf(coinsStr, sizeof(coinsStr), "%4d", coins);
    for(int i = 0; i < 4; i++) {
        writeCharToSegment(i, coinsStr[i]);
    }
}

//function to generate the random number and show it on the display
void displayRandomNumbers(int slotCount) {
    int numbers[4];
    for (int i = 0; i < slotCount; i++) {
        numbers[i] = rand() % 10; // Generate random number between 0 and 9
    }

    // Display all numbers simultaneously
    for (int i = 0; i < slotCount; i++) {
        writeNumberToSegment(i, numbers[i]);
    }

    // Check if all numbers are the same
    int win = 1;
    for (int i = 1; i < slotCount; i++) {
        if (numbers[i] != numbers[0]) {
            win = 0;
            break;
        }
    }
    if (win) {
        int winAmount = (slotCount == 2) ? WIN_AMOUNT_2 : (slotCount == 3) ? WIN_AMOUNT_3 : WIN_AMOUNT_4;
        coins += winAmount;
        printf("Congratulations! You won %d coins!\n", winAmount);
        //victorySound();
    }

    displayCoins(coins);
}

//function to chech if the game is over 
void checkGameOver() {
    if (coins <= 0) {
        printf("Game over! You have run out of coins.\n");
        while (1) {
            // Display scrolling loss message
        }
    } else if (coins >= MAX_COINS) {
        printf("Congratulations! Bank break! You have reached the maximum coins.\n");
        while (1) {
            // Display scrolling win message
        }
    }
}

//method to put in lib

void checkWin(int numbers[], int slotCount) {
    int winAmount = 0;
    int sameNumber = 1; // Flag to check if all numbers are the same
    int targetNumber = numbers[0]; // Store the first number as the target number

    // Checks if all numbers are the same
    for (int i = 1; i < slotCount; i++) {
        if (numbers[i] != targetNumber) {
            sameNumber = 0; // Set the flag to false if any number is different
            break;
        }
    }

    if (sameNumber) { // If all numbers are the same
        winAmount = (slotCount == 2) ? WIN_AMOUNT_2 : (slotCount == 3) ? WIN_AMOUNT_3 : WIN_AMOUNT_4;
        coins += winAmount; // Add the win amount to coins
        printf("Congratulations! You won %d coins!\n", winAmount);
        // i will play  victory sound here
    } else {
        printf("Better luck next time!\n");
    }

    displayCoins(coins); // Update coin display
}



int main() {
    // Initialization
    initUSART();
    initGame();
    initDisplay();
    srand(time(NULL));
    writeWelcomeToTheUserOnDisplay();
    DDRB |= _BV(PB2); // Enable LED control

    // Print game rules
    printf("----------------------------WELCOME TO ONE ARMED BANDIT!----------------\n ");
    _delay_ms(900);
    printf("-----------------------------------------------------------------------\n ");
    _delay_ms(900);
    printf("---$_$_$_$_$_$_$_$_$_$_$_$_$_$ RULES TO PLAY: _$_$_$_$_$_$_$_$_$_$_$_$\n ");
    _delay_ms(900);
    printGameRules();

    
    while (1) {
        if (bit_is_clear(PINC, BUTTON1)) {
            printf("Your choice is: 2 slots display.\n");
            coins--; // Deduct one coin for the bet
            displayCoins(coins); // Update coin display
            printf("We are starting the game! Your current bank is: %d coins\n", coins);

            // Blink LEDs twice
            lightUpMultipleLeds(0b0011);
            _delay_ms(1000);
            lightDownAllLeds();
            _delay_ms(1000);

            // Generate and display random numbers for 2 slots
            int numbers[2];
            for (int i = 0; i < 2; i++) {
                numbers[i] = rand() % 10; // Generate random number between 0 and 9
                writeNumberToSegment(i, numbers[i]); // Display the number
                _delay_ms(500); // it holds the number on display 500ms
            }

            checkWin(numbers, 2); // checks for win state 
            checkGameOver(); // it checks if the game is over 
        } else if (bit_is_clear(PINC, BUTTON2)) {
            //similar for 3 slots 
        } else if (bit_is_clear(PINC, BUTTON3)) {
            // Similar logic here for 4 slots display
        }
        writeNumber(coins); // Update coin display
    }

    return 0;
}



