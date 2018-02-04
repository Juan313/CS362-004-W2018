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
  struct gameState G, testG;
  int* kingdom = kingdomCards(smithy, adventurer, mine, village, feast, gardens,baron, steward, tribute, cutpurse);
  int seed = 1000;
  initializeGame(numPlayers, kingdom, seed, &G); 
  int *handPile, *deckPile, *discardPile;
  
  // case1: when the deck pile has more than 1 cards:
  printf("Begin  testing village card---------------------------------------\n");
  printf("case1: the deck contains at least one card-----------------:\n");

  handPile = malloc(4 * sizeof(int));
  deckPile = malloc(2 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));

  handPile =(int[4]){copper, village, smithy, estate};
  fillPile(&G, currentPlayer, 0, handPile, 4);
  deckPile =(int[2]){steward, curse};
  fillPile(&G, currentPlayer, 1, deckPile, 2);
  discardPile =(int[6]){curse, estate, silver, gold, smithy, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);
   
  memcpy(&testG, &G, sizeof(struct gameState));

  //printGameState(&G, currentPlayer); 
  cardEffectVillage(currentPlayer, &testG, 1);
  //printGameState(&testG, currentPlayer); 
  
  printf("testG.numActions = %d, expected = %d: ", testG.numActions, G.numActions+2); 
  asserttrue(testG.numActions == G.numActions+2); 
  int *handPileAfter, *deckPileAfter, *discardPileAfter;
  handPileAfter = malloc(4*sizeof(int));
  deckPileAfter = malloc(1*sizeof(int));  
  discardPileAfter = malloc(7*sizeof(int));  

  printf("testG.handCount[currentPlayer] = %d, expected = %d: ", testG.handCount[currentPlayer],G.handCount[currentPlayer]); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]); 

  handPileAfter =(int[4]){copper, smithy, estate, curse};
  printf("check that the hand pile is correct after village card being played: ");
  asserttrue(isSameArray(handPileAfter, testG.hand[currentPlayer], testG.handCount[currentPlayer]));

  printf("testG.deckCount[currentPlayer] = %d, expected = %d: ", testG.deckCount[currentPlayer],G.deckCount[currentPlayer]-1); 
  asserttrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]-1); 
  deckPileAfter =(int[1]){steward};
  printf("check that the deck pile is correct after village card being played: ");
  asserttrue(isSameArray(deckPileAfter, testG.deck[currentPlayer], testG.deckCount[currentPlayer]));

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer],G.discardCount[currentPlayer]+1); 
  asserttrue(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer]+1); 
  discardPileAfter =(int[7]){curse, estate, silver, gold, smithy, gardens, village};
  printf("check that the discard pile is correct after village card being played: ");
  asserttrue(isSameArray(discardPileAfter, testG.discard[currentPlayer],7)); 

  printf("check that the total cards are the same after village card is played: "); 
  int* joined1 = joinThreeArrays(G.hand[currentPlayer],G.handCount[currentPlayer],G.deck[currentPlayer], G.deckCount[currentPlayer], G.discard[currentPlayer], G.discardCount[currentPlayer]);
  int* joined2 = joinThreeArrays(testG.hand[currentPlayer],testG.handCount[currentPlayer],testG.deck[currentPlayer], testG.deckCount[currentPlayer], testG.discard[currentPlayer], testG.discardCount[currentPlayer]);
  asserttrue(isSameArray(joined1, joined2, 12));

  free(joined1);
  free(joined2);

  // case2: when the deck pile has 0 cards:
  printf("case2: the deck contains 0 card-----------------:\n");

  handPile = malloc(4 * sizeof(int));
  deckPile = malloc(0 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));

  handPile =(int[4]){copper, village, smithy, estate};
  fillPile(&G, currentPlayer, 0, handPile, 4);
  deckPile =(int[0]){};
  fillPile(&G, currentPlayer, 1, deckPile, 0);
  discardPile =(int[6]){curse, estate, silver, gold, smithy, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);
   
  memcpy(&testG, &G, sizeof(struct gameState));

  //printGameState(&G, currentPlayer); 
  cardEffectVillage(currentPlayer, &testG, 1);
  //printGameState(&testG, currentPlayer); 
  
  printf("testG.numActions = %d, expected = %d: ", testG.numActions, G.numActions+2); 
  asserttrue(testG.numActions == G.numActions+2); 

  handPileAfter = malloc(4*sizeof(int));
  deckPileAfter = malloc(5*sizeof(int));  
  discardPileAfter = malloc(0*sizeof(int));  

  printf("testG.handCount[currentPlayer] = %d, expected = %d: ", testG.handCount[currentPlayer],G.handCount[currentPlayer]); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]); 


  printf("testG.deckCount[currentPlayer] = %d, expected = %d: ", testG.deckCount[currentPlayer],G.discardCount[currentPlayer]-1); 
  asserttrue(testG.deckCount[currentPlayer] == G.discardCount[currentPlayer]-1); 

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer],1);
  asserttrue(testG.discardCount[currentPlayer] == 1);
  discardPileAfter =(int[1]){village};
  printf("check that the discard pile is correct after village card being played: ");
  asserttrue(isSameArray(discardPileAfter, testG.discard[currentPlayer],1)); 

  printf("check that the total cards are the same after village card is played: "); 
  joined1 = joinThreeArrays(G.hand[currentPlayer],G.handCount[currentPlayer],G.deck[currentPlayer], G.deckCount[currentPlayer], G.discard[currentPlayer], G.discardCount[currentPlayer]);
  joined2 = joinThreeArrays(testG.hand[currentPlayer],testG.handCount[currentPlayer],testG.deck[currentPlayer], testG.deckCount[currentPlayer], testG.discard[currentPlayer], testG.discardCount[currentPlayer]);
  asserttrue(isSameArray(joined1, joined2, 10));

  free(joined1);
  free(joined2);
  printf("End of testing village card---------------------------------------\n");
  printf("\n\n");
  return 0;
}
