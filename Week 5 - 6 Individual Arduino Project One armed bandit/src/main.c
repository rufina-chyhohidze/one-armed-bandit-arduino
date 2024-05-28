//TODO:IMPLEMENT POTENTIOMETER 
//TODO:IMPLEMENT CALLOC AND MALLOC 
//TODO:EXPAND THE README FILE
//TODO:Use of pointers and dynamic memory allocation
//Parameter “by value” and “by reference”


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
#define START_COINS 1000 //i decreased start coins, to play faster for a moment.
#define MAX_COINS 2000
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
#define DURATION 150 
#define MAX_GAME_STATES 10

int coins = START_COINS;

volatile unsigned long gameTimeSeconds = 0; 

typedef struct {
    int sequence;
    int coins;
    int wager;
    int displayValues[4];
    int winAmount;
} GameState;

const int ledPins[] = {LED1, LED2, LED3, LED4};
const int buttonPins[] = {BUTTON1, BUTTON2, BUTTON3};

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

//this function 
void displayGameTime() {
    int seconds = gameTimeSeconds / 60;
    printf("\nTotal game time: %d seconds\n", seconds);
}

void victorySound() {
  float  frequencies [] = {C4, E4, G4, C5, C5, G4, E4, C4, G4, A4, B4, C5, G4, E4, D4, C4}; // C D E C twice, followed by E F G once
enableBuzzer (); 
for ( int  note = 0 ; note < 8 ; note ++ ) 
{ 
  playTones ( frequencies [ note ], DURATION ); 
 custom_delay_us(150*1000); //wait 150 ms between the notes 
 } 
}

void lossSound() {
    float frequencies[] = {C5, B4, A4, G4, F4, E4, D4, C4}; // Descending pattern for loss sound
    int numNotes = sizeof(frequencies) / sizeof(frequencies[0]);
    enableBuzzer();
    for (int note = 0; note < numNotes; note++) {
        playTones(frequencies[note], DURATION);
        custom_delay_us(150 * 1000); // Wait 150 ms between the notes
    }
}


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
    } else if (coins >= MAX_COINS) {
        printf("Congratulations! Bank break! You have reached the maximum coins.\n");
        _delay_ms(1000);
        printf("Press the RESTART button to try your luck again!");
         displayGameTime(); // display total playing time in seconds in the end of the game.
        victorySound(); 
        while (1) {
           //shows winning 7777!!!
            writeNumber(7777);
           
            
        }
    }
}

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
    } else {
        printf("Better luck next time!\n");
    }

    displayCoins(coins); // Update coin display
}
 /*int bet = 1;
  void makeBet(){
          uint16_t adcValue = ADC;
    int displayValue = ((adcValue * 20)/1024)+ 1  ; // Scale to range 1-10
    writeNumber(displayValue); // Display the scaled value
    printf("Your bet is: %d\n", displayValue); // Print the bet value
    
    // Check if the display value exceeds the maximum bet
    if (displayValue > coins) {
        printf("Insufficient coins for this bet! Setting the maximum bet.\n");
        displayValue = coins; // Set the bet amount to the maximum coins
    }
    
    bet = displayValue; // Update the bet value
    coins -= bet; // Subtract the bet from current coins

    // Display the current coins after the bet
    displayCoins(coins);
        //_delay_ms(0.100);
    };
    */



int main() {
    // Initialization
    initADC();
    initUSART();
    initGame();
    initDisplay();
    initTimer(); //enables timer routine and ISR
    srand(time(NULL));
    writeWelcomeToTheUserOnDisplay();
    DDRB |= _BV(PB2); 
    

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
            //makeBet();
            coins--;
            //coins-= bet; // substract one coin for the bet
            displayCoins(coins); // Update coin display
            printf("We are starting the game! Your current bank is: %d coins\n", coins);
            rollOnDisplay();
            

            //this loop makes 2 leds blinks twice,and then it generate numbers.
            for(int i=0;i<2;i++){
            lightUpMultipleLeds(0b0011);
            _delay_ms(200);
            lightDownAllLeds();
            _delay_ms(200);
            }

            // Generate and display random numbers for 2 slots
            int numbers[2];
            for (int i = 0; i < 2; i++) {
                numbers[i] = rand() % 10; // Generate random number between 0 and 9
                writeNumberToSegment(i, numbers[i]); // Display the number
                _delay_ms(800); // it holds the number on display 500ms
                
            }
            checkWin(numbers, 2); // checks for win state, 2 same numbers in a ROW!
            checkGameOver(); // it checks if the game is over 
        } else if (bit_is_clear(PINC, BUTTON2)) {
            //similar pattern for 3 slots 
             printf("Your choice is: 3 slots display.\n");
            coins--; // substract one coin for the bet
            displayCoins(coins); // Update coin display
            printf("We are starting the game! Your current bank is: %d coins\n", coins);
            rollOnDisplay();

            //this loop blink 3 leds 3 times
            for(int i=0;i<3;i++){
            lightUpMultipleLeds(0b0111);
            _delay_ms(150);
            lightDownAllLeds();
            _delay_ms(150);
            } 

            // Generate and display random numbers for 2 slots
            int numbers[3];
            for (int i = 0; i < 3; i++) {
                numbers[i] = rand() % 10; // Generate random number between 0 and 9
                writeNumberToSegment(i, numbers[i]); // Display the number
                _delay_ms(800); // it holds the number on display 500ms
            }
            checkWin(numbers, 3);// 3 same numbers in a ROW!
            checkGameOver();  

        } else if (bit_is_clear(PINC, BUTTON3)) {
               printf("Your choice is: 4 slots display.\n");
            coins--; // substract one coin for the bet
            displayCoins(coins); // Update coin display
            printf("We are starting the game! Your current bank is: %d coins\n", coins);
            rollOnDisplay(); //shows the animation of roll on display

            //this loop blink 4 leds 4 times 
            for (int i=0;i<4;i++){
            lightUpMultipleLeds(0b1111);
            _delay_ms(150);
            lightDownAllLeds();
            _delay_ms(150);
            }

            // Generate and display random numbers for 2 slots
            int numbers[4];
            for (int i = 0; i < 4; i++) {
                numbers[i] = rand() % 10; // Generate random number between 0 and 9
                writeNumberToSegment(i, numbers[i]); // Display the number
                _delay_ms(800); // it holds the number on display 500ms
            }
            checkWin(numbers, 4);// 4 same numbers in a ROW!
            checkGameOver();  
            
        }
        writeNumber(coins); 
    }

    return 0;
}


/*
    for(int i = 4; i>-1;i--){
        enabledLed(i)
    }
    while(1){
        for(int i=4;i>-1;i--){
            lightUpLed(i);
            _delay_ms(1000);
        }
         for(int i=4;i>-1;i--){
            lightUpLed(i);
            _delay_ms(1000);
        }
        break;

    }
    */

