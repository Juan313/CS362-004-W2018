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
  
  handPile = malloc(5 * sizeof(int));
  deckPile = malloc(3 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));

  handPile =(int[5]){copper, silver, smithy, estate, copper};
  fillPile(&G, currentPlayer, 0, handPile, 5);
  deckPile =(int[3]){curse, steward, gold};
  fillPile(&G, currentPlayer, 1, deckPile, 4);
  discardPile =(int[6]){curse, estate, silver, gold, village, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);

  printGameState(&G, currentPlayer);
   
  // copy a gameState from the original gameState
  memcpy(&testG, &G, sizeof(struct gameState));
  cardEffectSmithy(currentPlayer, &testG, 2);
  
  printGameState(&testG, currentPlayer);

  /*
  printf("Beging testing discardCard() function. Case 1. ----------------------\n");
  discardCard(handPos, 0, &testG, 1); 

  printf("Testing that the deck pile remain the same after discardCard() being called: ");
  asserttrue(isSameArray(testG.deck[currentPlayer], G.deck[currentPlayer], testG.deckCount[currentPlayer]));

  printf("testG.deckCount[currentPlayer] = %d, expected = %d: ", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]); 
  asserttrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]); 

  printf("testG.handcount = %d, expected = %d: ", testG.handCount[currentPlayer], G.handCount[currentPlayer]-1); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]-1); 
  int* newHandArray = removeElementFromArray(G.hand[currentPlayer], G.handCount[currentPlayer], handPos);
  printf("Testing that the hand card pile is the same after removing from original hand: ");
  asserttrue(isSameArray(testG.hand[currentPlayer], newHandArray, testG.handCount[currentPlayer]));
  free(newHandArray);

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]); 
  asserttrue(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer]); 

  printf("Testing that the discard pile remain the same after discardCard() being called: ");
  asserttrue(isSameArray(testG.discard[currentPlayer], G.discard[currentPlayer], testG.discardCount[currentPlayer]));

  printf("testG.playedCardCount = %d, expected = %d: ", testG.playedCardCount, G.playedCardCount+1); 
  asserttrue(testG.playedCardCount == G.playedCardCount + 1); 

  printf("Testing that the last element of playCard in testG is the same as the current hand in gameState G: ");
  asserttrue(testG.playedCards[testG.playedCardCount-1] == G.hand[currentPlayer][handPos]);
  printf("Tesing that the playedcard pile is the same as before after removing the last element: ");
  int* newPlayedArray = removeElementFromArray(testG.playedCards, testG.playedCardCount, testG.playedCardCount-1);
  asserttrue(isSameArray(G.playedCards,newPlayedArray, G.playedCardCount));
  free(newPlayedArray);

  // test case 2: if the card is discarded, the discard pile should increase count by 1, the last element of discard pile should be the discarded card.
  
  printf("Beging testing discardCard() function. Case 2. ----------------------\n");
  memcpy(&testG, &G, sizeof(struct gameState));
  discardCard(handPos, 0, &testG, 0); 

  //printGameState(&G, currentPlayer);
  //printGameState(&testG, currentPlayer);
  printf("Testing that the deck pile remain the same after discardCard() being called: ");
  asserttrue(isSameArray(testG.deck[currentPlayer], G.deck[currentPlayer], testG.deckCount[currentPlayer]));

  printf("testG.deckCount[currentPlayer] = %d, expected = %d: ", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]); 
  asserttrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]); 

  printf("testG.handcount = %d, expected = %d: ", testG.handCount[currentPlayer], G.handCount[currentPlayer]-1); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]-1); 
  newHandArray = removeElementFromArray(G.hand[currentPlayer], G.handCount[currentPlayer], handPos);
  printf("Testing that the hand card pile is the same after removing from original hand: ");
  asserttrue(isSameArray(testG.hand[currentPlayer], newHandArray, testG.handCount[currentPlayer]));
  free(newHandArray);

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]+1); 
  asserttrue(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer]+1); 

  printf("Tesing that the discard pile is the same as before after removing the last element: ");
  int* newDiscard = removeElementFromArray(testG.discard[currentPlayer],testG.discardCount[currentPlayer], testG.discardCount[currentPlayer]-1);
  asserttrue(isSameArray(newDiscard, G.discard[currentPlayer], G.discardCount[currentPlayer]));

  printf("Testing that the last element of discard pile in testG is the same as the current hand in gameState G: ");
  asserttrue(testG.discard[currentPlayer][testG.discardCount[currentPlayer]-1] == G.hand[currentPlayer][handPos]);

  printf("testG.playedCardCount = %d, expected = %d: ", testG.playedCardCount, G.playedCardCount); 
  asserttrue(testG.playedCardCount == G.playedCardCount); 

  printf("Testing that the playedCard pile remain the same after discardCard() being called: ");
  asserttrue(isSameArray(testG.playedCards, G.playedCards, G.playedCardCount));
  */
  return 0;
}
