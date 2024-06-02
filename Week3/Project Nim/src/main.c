#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "led.h"
#include "display.h"
#include "buttons.h"
#include "potentio.h"

#define START_NUMBER 21
#define MAX_NUMBER 3

// Global variables
int matches = START_NUMBER;
int player_turn = 1; // 1 for Player, 0 for Computer
int matches_to_take = 1; // Number of matches the player wants to take

// Structure to keep track of game progress
typedef struct {
    int turn;
    int player; // 1 for Player, 0 for Computer
    int matches_taken;
    int matches_left;
} GameLog;

GameLog *game_logs;
int game_log_count = 0;
int game_log_size = 10;


int main() {
  
    initGame();
}

void initGame() {
    // Initialize components
    initDisplay();
    initADC();
  
    // Generate random seed using potentiometer
    srand(potentioMeterNumber());
    int seed = rand() % 10000;
    writeNumberAndWait(seed, 2000);

    // Allocate memory for game logs
    game_logs = (GameLog*) calloc(game_log_size, sizeof(GameLog));
    
    // Display initial match count and who starts
    //displayStatus();

    // Determine who starts the game
    player_turn = rand() % 2;
}

