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

/*volatile int coins = START_COINS;
volatile int wager = 1;
volatile int displayCount = 4;
volatile int gameActive = 0;
volatile int showCoins = 0;
volatile int symbols[4] = {0, 0, 0, 0};
*/

#define MAX_GAME_STATES 10

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

int main() {
    initUSART();
    initGame();
    DDRB |= _BV(PB2); //controlling an LED
    DDRB |= _BV(PB3);
    DDRB |= _BV(PB4);
    DDRB |= _BV(PB5);
    
    printf("----------------------------WELCOME TO ONE ARMED BANDIT!----------------\n ");
    _delay_ms(1000);
    printf("-----------------------------------------------------------------------\n ");
    _delay_ms(1000);
    printf("---$_$_$_$_$_$_$_$_$_$_$_$_$_$ RULES TO PLAY: _$_$_$_$_$_$_$_$_$_$_$_$\n ");
    _delay_ms(1000);
    printGameRules();
    
     while (1) {
         if (bit_is_clear(PINC, BUTTON1)) {
            printf("Your choice is: 2 slots display.\n");
            // Blink LEDs twice
            for (int i = 0; i < 2; i++) {
                lightUpAllLeds();
                _delay_ms(500);
                lightDownAllLeds();
                _delay_ms(500);
            }
        } else if (bit_is_clear(PINC, BUTTON2)) {
            printf("Your choice is: 3 slots display.\n");
            // Blink LEDs three times
            for (int i = 0; i < 3; i++) {
                lightUpAllLeds();
                _delay_ms(500);
                lightDownAllLeds();
                _delay_ms(500);
            }
        } else if (bit_is_clear(PINC, BUTTON3)) {
            printf("Your choice is: 4 slots display.\n");
            // Blink LEDs four times
            for (int i = 0; i < 4; i++) {
                lightUpAllLeds();
                _delay_ms(500);
                lightDownAllLeds();
                _delay_ms(500);
            }
        }
    }

    return 0;
}



