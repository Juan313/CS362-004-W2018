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

#define MAX(a,b) ((a) > (b) ? a : b)

int main(){
  
  // initialize a game
  int numPlayers = 3;
  int currentPlayer = 1;
  struct gameState G, testG;
  int* kingdom = kingdomCards(smithy, adventurer, mine, village, feast, gardens,baron, steward, tribute, cutpurse);
  int seed = 1000;
  initializeGame(numPlayers, kingdom, seed, &G); 
  int *handPile, *deckPile, *discardPile, *playedPile;
  
  printf("Begin  testing remodel card---------------------------------------\n");

  handPile = malloc(4 * sizeof(int));
  deckPile = malloc(2 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));
  playedPile = malloc(2 * sizeof(int));

  handPile =(int[4]){remodel, village, gold, estate};
  fillPile(&G, currentPlayer, 0, handPile, 4);
  deckPile =(int[2]){steward, curse};
  fillPile(&G, currentPlayer, 1, deckPile, 2);
  discardPile =(int[6]){curse, estate, silver, gold, province, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);
  playedPile =(int[2]){copper, curse};
  fillPile(&G, currentPlayer, 3, playedPile, 2);
   
  memcpy(&testG, &G, sizeof(struct gameState));

  //printGameState(&G, currentPlayer); 
  cardEffectRemodel(currentPlayer, &testG, 3, smithy, 0);
  //printGameState(&testG, currentPlayer); 
  
  
  printf("testG.numActions = %d, expected = %d: ", testG.numActions, G.numActions); 
  asserttrue(testG.numActions == G.numActions); 

  int *handPileAfter, *deckPileAfter, *discardPileAfter, *playedPileAfter;
  handPileAfter = malloc(2*sizeof(int));
  deckPileAfter = malloc(2*sizeof(int));  
  discardPileAfter = malloc(8*sizeof(int));  

  printf("testG.handCount[currentPlayer] = %d, expected = %d: ", testG.handCount[currentPlayer],G.handCount[currentPlayer]-2); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]-2); 

  handPileAfter =(int[2]){village, gold};
  printf("check that the hand pile is correct after remodel card being played: ");
  asserttrue(isSameArray(handPileAfter, testG.hand[currentPlayer], testG.handCount[currentPlayer]));

  printf("testG.deckCount[currentPlayer] = %d, expected = %d: ", testG.deckCount[currentPlayer],G.deckCount[currentPlayer]); 
  asserttrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]); 
  deckPileAfter =(int[2]){steward,curse};
  printf("check that the deck pile is correct after remodel card being played: ");
  asserttrue(isSameArray(deckPileAfter, testG.deck[currentPlayer], testG.deckCount[currentPlayer]));

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer],G.discardCount[currentPlayer]+2); 
  asserttrue(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer]+2); 
  discardPileAfter =(int[8]){curse, estate, silver, gold, province, gardens, remodel, smithy};
  printf("check that the discard pile is correct after remodel card being played: ");
  asserttrue(isSameArray(discardPileAfter, testG.discard[currentPlayer],8)); 

  printf("testG.playedCardCount = %d, expected = %d: ", testG.playedCardCount,G.playedCardCount+1); 
  asserttrue(testG.playedCardCount == G.playedCardCount+1); 
  playedPileAfter =(int[3]){copper, curse, estate};
  printf("check that the played pile is correct after remodel card being played: ");
  asserttrue(isSameArray(playedPileAfter, testG.playedCards,MAX(3, testG.playedCardCount))); 

  return 0;
}
