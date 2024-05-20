#include <avr/io.h> 
#include <stdlib.h> 
#include <usart.h> 
#include <util/delay.h> 
#include <string.h> 

typedef struct 
{
  int value;
  char* suit;
} CARD;

void fullDeck (CARD* deck)
{
  char suits[4][10] = {"hearts", "diamonds", "spades", "clubs"};
  int index;
  for (int i = 0;i<4;i++){
    for( int j=0;j<13;j++){
            //TODO: use malloc to reserve just enough space for the suit 
            //TODO: copy the color to the allocated address space 
            //TODO: set the card's value 
      index = (i * 13)+ j;
      deck[index].suit = (char*)malloc(strlen(suits[i]) + 1);
      strcpy(deck[index].suit, suits[i]);
      deck[index].value= j + 1;
    }
  }
}

void showCard(CARD* theCard){
  switch (theCard->value){
    //printf( "ace of %s", theCard.suit ); updated to ->
    //The -> operator is used to access members of a structure through a pointer.
    case 1:
    printf("ace of %s", theCard->suit);// Access the value field of the structure pointed to by theCard
    break;
    case 11: 
            printf("jack of %s", theCard->suit); 
            break; 
        case 12: 
            printf("queen of %s", theCard->suit); 
            break; 
        case 13: 
            printf("king of %s", theCard->suit); 
            break; 
        default: 
            printf("%d of %s", theCard->value, theCard->suit); 
    } 
  }

  CARD* drawCard(CARD deck[])//: Declares that the function returns a pointer to a CARD.
  {
    int randm = rand() % 52;
     //TODO: return the address of the random card 
    return &deck[randm]; 
  }

  int main(){
    initUSART();
    //TODO: use calloc to make the deck of cards 
    CARD* deck = (CARD*)calloc(52,sizeof(CARD));
    fullDeck(deck);

 //TODO: update the following code so that it compiles 
    for (int i = 0;i<10;i++)
    {
      CARD* card = drawCard(deck);
      showCard(card);
      printf("\n");
    }
       //TODO: free all allocated memory: 
    for(int i = 0; i <52; i++){
      free(deck[i].suit);
    }
    free(deck);

     return 0;
  }
  /* malloc:

Useful when you need a single block of memory.
Efficient but requires manual initialization if zero-initialization is needed.
Example: Allocating memory for a single object or a non-initialized array.
*/

/*calloc:

Useful for allocating memory for arrays or structures where zero-initialization is beneficial.
Ensures all elements are set to zero, avoiding potential issues with uninitialized memory.
Example: Allocating memory for an array of structures or initializing buffers.*/
 
