//README FILE for this project done, go check it out!
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "led.h"
#include "display.h"
#include "buttons.h"
#include "potentio.h"
#include <avr/interrupt.h>

#define START_MATCHES 21
#define MAX_REMOVAL 3

#define BUTTON1 PC1
#define BUTTON2 PC2
#define BUTTON3 PC3

// structure to log the game progress
typedef struct {
    int turn;
    char player; // p for player , c for computer
    int removed_matches;
    int remaining_matches;
} GameLog;

// global variables
char playerTurn;
int removalCount = MAX_REMOVAL;
int remainingMatches = START_MATCHES;
char computerMoveDisplay[4];

// dynamic memory allocation for game logs
GameLog *gameLogs;
int logCount = 0;
int logCapacity = 10;

void startMatch() {
    uint8_t startPressed = 0;
    while (startPressed == 0) {
        ADCSRA |= (1 << ADSC);  
        loop_until_bit_is_clear(ADCSRA, ADSC);  
        uint16_t adcValue = ADC;  
        writeNumber(adcValue);
        if (buttonPushed(0) == 1) {
            startPressed = 1;
            srand(adcValue);
            _delay_ms(500);
        }
    }
}

char determineFirstPlayer() {
    return (rand() % 2 == 1) ? 'p' : 'c';
}

ISR(PCINT1_vect) {
    if (buttonPushed(0) && playerTurn == 'p') {
        _delay_us(1000);
        if (buttonPushed(0)) {
            if (removalCount > 1) removalCount--;
        }
    }
    if (buttonPushed(2) && playerTurn == 'p') {
        _delay_us(1000);
        if (buttonPushed(2)) {
            if (removalCount < MAX_REMOVAL && removalCount + 1 <= remainingMatches) removalCount++;
        }
    }
    if (buttonPushed(1)) {
        _delay_us(1000);
        if (buttonPushed(1)) {
            if (playerTurn == 'p') {
                remainingMatches -= removalCount;
                playerTurn = 'c';
                logProgress(logCount++, 'p', removalCount, remainingMatches);
                removalCount = MAX_REMOVAL;
            } else if (playerTurn == 'c') {
                int computerMove = (remainingMatches - 1) % (MAX_REMOVAL + 1);
                if (computerMove == 0) {
                    computerMove = (rand() % MAX_REMOVAL) + 1;
                }
                removalCount = computerMove;
                snprintf(computerMoveDisplay, sizeof(computerMoveDisplay), "%d%c%02d", computerMove, playerTurn, remainingMatches);
                writeStringAndWait(computerMoveDisplay, 1000);
                remainingMatches -= removalCount;
                playerTurn = 'p';
                logProgress(logCount++, 'c', removalCount, remainingMatches);
                removalCount = MAX_REMOVAL;
            }
        }
    }
}

void initializeGame() {
    initUSART();
    initDisplay();
    printf("\nGet ready to play!\n");
    _delay_ms(500);
    printf("Press button 1 to start.");
    
    initADC();
    enableButton(0);
    enableButton(1);
    enableButton(2);

    gameLogs = (GameLog*) calloc(logCapacity, sizeof(GameLog));
    playerTurn = determineFirstPlayer();
    startMatch();
    
    PCICR |= _BV(PCIE1);  
    PCMSK1 |= (_BV(PC1) | _BV(PC2) | _BV(PC3));  
    sei();
}

void handleMatchUpdate(int count) {
    remainingMatches -= count;
    if (remainingMatches < 1) remainingMatches = 1;
}

void logProgress(int turn, char player, int removed, int remaining) {
    if (logCount >= logCapacity) {
        logCapacity *= 2;
        GameLog *newLogs = (GameLog*) malloc(logCapacity * sizeof(GameLog));
        for (int i = 0; i < logCount; i++) {
            newLogs[i] = gameLogs[i];
        }
        free(gameLogs);
        gameLogs = newLogs;
    }

    gameLogs[logCount].turn = turn;
    gameLogs[logCount].player = player;
    gameLogs[logCount].removed_matches = removed;
    gameLogs[logCount].remaining_matches = remaining;
}

void showWinner(char winner) {
    if (winner == 'p') {
        for(int i = 0; i < 50; i++){
            writeCharToSegment(0,'G');
            _delay_ms(5);
            writeCharToSegment(1,'O');
            _delay_ms(10);
            writeCharToSegment(2,'O');
            _delay_ms(15);
            writeCharToSegment(3,'D');
            _delay_ms(15);
        }
    } else {
        for(int i = 0; i < 50; i++){
            writeCharToSegment(0,'L');
            _delay_ms(5);
            writeCharToSegment(1,'O');
            _delay_ms(10);
            writeCharToSegment(2,'S');
            _delay_ms(15);
            writeCharToSegment(3,'S');
            _delay_ms(15);
        }
    }
}

void displayCurrentStatus() {
    writeNumberToSegment(0, removalCount);
    writeCharToSegment(1, playerTurn);
    writeNumberToSegment(2, remainingMatches / 10);
    writeNumberToSegment(3, remainingMatches % 10);

    //duplicat4e print statemnet to serail monitor
    printf("Current Status:\n");
    printf("Removal Count: %d\n", removalCount);
    printf("Player Turn: %c\n", playerTurn);
    printf("Remaining Matches: %d\n", remainingMatches);
}

void updateDisplay() {
    //  to maintain brightness i did this function
    writeNumberToSegment(0, removalCount);
    _delay_ms(1000);
    writeCharToSegment(1, playerTurn);
    _delay_ms(1000);
    writeNumberToSegment(2, remainingMatches / 10);
    _delay_ms(1000);
    writeNumberToSegment(3, remainingMatches % 10);
    _delay_ms(1000);
}

    int main() {
    initializeGame();
    sei();

    while (remainingMatches > 1) {
        displayCurrentStatus(); // Display the current status
        while (!buttonPushed(1)) {} // Wait for button press to proceed
        _delay_ms(100); // delay 
        updateDisplay(); 
        _delay_ms(1500); // Pause between turns
        if (remainingMatches <= 1) break; // checks if the game over
        displayCurrentStatus(); // 
        while (buttonPushed(1)) {} //
        _delay_ms(100); 
        while (!buttonPushed(1)) {} 
        _delay_ms(100); 
        updateDisplay();
        _delay_ms(1000); 
    }

    showWinner(playerTurn);
    free(gameLogs);

    return 0;
}
