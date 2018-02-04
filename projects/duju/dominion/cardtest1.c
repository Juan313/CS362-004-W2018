#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helper.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>



int main(){
  
  // initialize a game
  int numPlayers = 3;
  int currentPlayer = 1;
  struct gameState G,testG;
  int* kingdom = kingdomCards(smithy, adventurer, mine, village, feast, gardens,baron, steward, tribute, cutpurse);
  int seed = 1000;
  initializeGame(numPlayers, kingdom, seed, &G); 
  int *handPile, *deckPile, *discardPile;
  
  // case1: when the deck pile has more than 3 cards:
  printf("Begin  testing smithy card---------------------------------------\n");
  printf("case 1: when the deck pile has more than 3 cards:----------------\n");
  handPile = malloc(5 * sizeof(int));
  deckPile = malloc(3 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));

  handPile =(int[5]){copper, silver, smithy, estate, copper};
  fillPile(&G, currentPlayer, 0, handPile, 5);
  deckPile =(int[3]){curse, steward, gold};
  fillPile(&G, currentPlayer, 1, deckPile, 3);
  discardPile =(int[6]){curse, estate, silver, gold, village, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);
   
  // copy a gameState from the original gameState
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffectSmithy(currentPlayer, &testG, 2);
  
  printf("testG.numActions = %d, expected = %d: ", testG.numActions, G.numActions); 
  asserttrue(testG.numActions == G.numActions); 
  printf("testG.handCount[currentPlayer] = %d, expected = %d: ", testG.handCount[currentPlayer], G.handCount[currentPlayer]+2); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]+2); 
  printf("Testing that the content of the hand pile is correct after smithy is played:  ");
  int* newHandPile = removeElementFromArray(G.hand[currentPlayer], G.handCount[currentPlayer], 2);
  newHandPile = addElementToArray(newHandPile, G.handCount[currentPlayer]-1, G.deck[currentPlayer][G.deckCount[currentPlayer]-1]);
  newHandPile = addElementToArray(newHandPile, G.handCount[currentPlayer], G.deck[currentPlayer][G.deckCount[currentPlayer]-2]);
  newHandPile = addElementToArray(newHandPile, G.handCount[currentPlayer]+1, G.deck[currentPlayer][G.deckCount[currentPlayer]-3]);
  asserttrue(isSameArray(newHandPile, testG.hand[currentPlayer], testG.handCount[currentPlayer]));

  printf("testG.deckCount[currentPlayer] = %d, expected = %d: ", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]-3); 
  asserttrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]-3); 
  printf("Testing that the content of the deck pile is correct after smithy is played:  ");
  int size = G.deckCount[currentPlayer];
  int* newDeckPile = removeElementFromArray(G.deck[currentPlayer], size, size-1);
  newDeckPile = removeElementFromArray(newDeckPile, size-1, size-2);
  newDeckPile = removeElementFromArray(newDeckPile, size-2, size-3);
  asserttrue(isSameArray(newDeckPile, testG.deck[currentPlayer], size-3));

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]+1); 
  asserttrue(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer]+1); 
  printf("Testing that the content of the discard pile is correct after smithy is played:  ");
  size = G.discardCount[currentPlayer];
  int* newDiscardPile = addElementToArray(G.discard[currentPlayer],size,smithy);
  asserttrue(isSameArray(newDiscardPile, testG.discard[currentPlayer], size+1));


  // case2: when the deck pile has less than 3 cards:
  printf("Begin  testing smithy card---------------------------------------\n");
  printf("case 2: when the deck pile has less than 3 cards:----------------\n");
  handPile = malloc(5 * sizeof(int));
  deckPile = malloc(1 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));

  handPile =(int[5]){copper, silver, smithy, estate, copper};
  fillPile(&G, currentPlayer, 0, handPile, 5);
  deckPile =(int[1]){curse};
  fillPile(&G, currentPlayer, 1, deckPile, 1);
  discardPile =(int[6]){duchy, estate, silver, gold, village, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);

  //printGameState(&G, currentPlayer);
   
  // copy a gameState from the original gameState
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffectSmithy(currentPlayer, &testG, 2);
  //printGameState(&testG, currentPlayer);
  
  printf("testG.numActions = %d, expected = %d: ", testG.numActions, G.numActions); 
  asserttrue(testG.numActions == G.numActions); 
  printf("testG.handCount[currentPlayer] = %d, expected = %d: ", testG.handCount[currentPlayer], G.handCount[currentPlayer]+2); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]+2); 

  printf("testG.deckCount[currentPlayer] = %d, expected = %d: ", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]+G.discardCount[currentPlayer]-3); 
  asserttrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]+G.discardCount[currentPlayer]-3); 

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer],1); 
  asserttrue(testG.discardCount[currentPlayer] == 1); 

  printf("Test that the content of the full deck remains the same after the smithy card being played: ");
  size = G.handCount[currentPlayer];
  int* hand = removeElementFromArray(G.hand[currentPlayer],size, 2);
  size--;
  int size1 = size;

  int size2 = G.deckCount[currentPlayer];
  int* arr2 = G.deck[currentPlayer];
  int* joined = joinArrays(hand, size1, arr2, size2);
  int* joined2 = joinArrays(joined, size1+size2, G.discard[currentPlayer], G.discardCount[currentPlayer]);

  int* joined3 = joinArrays(testG.hand[currentPlayer], testG.handCount[currentPlayer], testG.deck[currentPlayer], testG.deckCount[currentPlayer]);
  //printArray(joined2, size1+size2+G.discardCount[currentPlayer]);
//  printArray(joined3, testG.handCount[currentPlayer]+testG.deckCount[currentPlayer]);
   
  asserttrue(isSameArray(joined2, joined3,size1+size2+G.discardCount[currentPlayer]));
  printf("End of testing smithy card---------------------------------------\n");
  printf("\n\n"); 
  return 0;
}
