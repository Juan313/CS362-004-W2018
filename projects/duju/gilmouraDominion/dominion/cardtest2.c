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
  struct gameState G;
  int* kingdom = kingdomCards(smithy, adventurer, mine, village, feast, gardens,baron, steward, tribute, cutpurse);
  int seed = 1000;
  initializeGame(numPlayers, kingdom, seed, &G); 
  int *handPile, *deckPile, *discardPile;
  
  // case1: when the deck pile has more than 3 cards:
  printf("Begin  testing adventurer card---------------------------------------\n");
  printf("case1: the deck contains at least two treasure card-----------------:\n");

  int numAction = G.numActions; 
  
  printf("G.numActions = %d, expected = %d: ", G.numActions, numAction); 
  asserttrue(G.numActions == numAction); 

  handPile = malloc(4 * sizeof(int));
  deckPile = malloc(5 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));

  handPile =(int[4]){copper, adventurer, smithy, estate};
  fillPile(&G, currentPlayer, 0, handPile, 4);
  deckPile =(int[5]){curse, steward, gold, smithy, silver};
  fillPile(&G, currentPlayer, 1, deckPile, 5);
  discardPile =(int[6]){curse, estate, silver, gold, village, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);
   
//  printGameState(&G, currentPlayer); 
  int temphand[MAX_HAND];
  //adventurerF(currentPlayer, &G, 1);
  adventurerF(currentPlayer, &G, temphand, 0, 0, 0);
//  printGameState(&G, currentPlayer); 
  
  int *handPileAfter, *deckPileAfter, *discardPileAfter;
  handPileAfter = malloc(6*sizeof(int));
  deckPileAfter = malloc(2*sizeof(int));  
  discardPileAfter = malloc(7*sizeof(int));  

  handPileAfter =(int[6]){copper, adventurer, smithy, estate, silver, gold};
  deckPileAfter =(int[2]){curse, steward};
  discardPileAfter =(int[7]){curse, estate, silver, gold, village, gardens, smithy};

  printf("G.handCount[currentPlayer] = %d, expected = %d: ", G.handCount[currentPlayer],6); 
  asserttrue(G.handCount[currentPlayer] == 6); 
  printf("check that the hand pile is correct after adventurer card being played: ");

  asserttrue(isSameArray(handPileAfter, G.hand[currentPlayer], G.handCount[currentPlayer]));

  printf("G.deckCount[currentPlayer] = %d, expected = %d: ", G.deckCount[currentPlayer],2); 
  asserttrue(G.deckCount[currentPlayer] == 2); 
  printf("check that the deck pile is correct after adventurer card being played: ");
  asserttrue(isSameArray(deckPileAfter, G.deck[currentPlayer], G.deckCount[currentPlayer]));

  printf("G.discardCount[currentPlayer] = %d, expected = %d: ", G.discardCount[currentPlayer],7); 
  asserttrue(G.discardCount[currentPlayer] == 7); 
  printf("check that the discard pile is correct after adventurer card being played: ");
  asserttrue(isSameArray(discardPileAfter, G.discard[currentPlayer], G.discardCount[currentPlayer]));

  // case2: the deck contains less than two treasure card
  printf("case2: the deck contains less than two treasure card------------------\n");

  handPile = malloc(4 * sizeof(int));
  deckPile = malloc(4 * sizeof(int));
  discardPile = malloc(6 * sizeof(int));

  handPile =(int[4]){copper, adventurer, smithy, estate};
  fillPile(&G, currentPlayer, 0, handPile, 4);
  deckPile =(int[4]){curse, steward, gold, smithy};
  fillPile(&G, currentPlayer, 1, deckPile, 4);
  discardPile =(int[6]){curse, estate, silver, gold, village, gardens};
  fillPile(&G, currentPlayer, 2, discardPile, 6);
  
  numAction = G.numActions; 
  //printGameState(&G, currentPlayer); 
  adventurerF(currentPlayer, &G, temphand, 0, 0, 0);
  //printGameState(&G, currentPlayer); 
  
  printf("G.numActions = %d, expected = %d: ", G.numActions, numAction); 
  asserttrue(G.numActions == numAction); 
  discardPileAfter =(int[3]){curse, steward, smithy};

  printf("G.handCount[currentPlayer] = %d, expected = %d: ", G.handCount[currentPlayer],6); 
  asserttrue(G.handCount[currentPlayer] == 6); 

  printf("check that the newly drawn cards in the hand are treasure cards: "); 
  int card =G.hand[currentPlayer][G.handCount[currentPlayer]-1];  
  asserttrue((card>=copper) && (card<=gold));
  printf("check that the second-to-last drawn cards in the hand is gold: "); 
  card = G.hand[currentPlayer][G.handCount[currentPlayer]-2];  
  asserttrue(card==gold);

  printf("G.deckCount[currentPlayer] = %d, expected = %d: ", G.deckCount[currentPlayer],5); 
  asserttrue(G.deckCount[currentPlayer] == 5); 

  printf("G.discardCount[currentPlayer] = %d, expected = %d: ", G.discardCount[currentPlayer],3); 
  asserttrue(G.discardCount[currentPlayer] == 3); 
  printf("check that the discard pile is correct after adventurer card being played: ");
  asserttrue(isSameArray(discardPileAfter, G.discard[currentPlayer], G.discardCount[currentPlayer]));

  printf("check that the total cards are the same after treasurer card is played: "); 
  int* joined1 = joinThreeArrays(handPile,4,deckPile,4,discardPile,6);
  int* joined2 = joinThreeArrays(G.hand[currentPlayer],G.handCount[currentPlayer],G.deck[currentPlayer], G.deckCount[currentPlayer], G.discard[currentPlayer], G.discardCount[currentPlayer]);
  asserttrue(isSameArray(joined1, joined2, 14));
  printf("End of testing adventurer card---------------------------------------\n");
  printf("\n\n");
  return 0;
}
