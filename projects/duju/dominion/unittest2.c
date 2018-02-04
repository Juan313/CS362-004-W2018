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
  int numPlayers = 2;
  int currentPlayer = 0;
  struct gameState G,testG;
  memset(&G, 23, sizeof(struct gameState));
  memset(&testG, 23, sizeof(struct gameState));
  int seed = 1000;
  int* kingdom = kingdomCards(smithy, adventurer, mine, village, feast, gardens,baron, steward, tribute, cutpurse);
  initializeGame(numPlayers, kingdom, seed, &G); 
  int j = 1;
  while(j>0){
    int rand = floor(Random()*10);
    G.discard[currentPlayer][G.discardCount[currentPlayer]]= kingdom[rand];
    G.discardCount[currentPlayer]++;
    j--;
  }

  // run drawCard function on the original gameState
  // compare the gameState before and after drawCard function is run 
  // test case 1: if the deck is empty:  after drawCard is called, the deck pile 
  // should be full, the discard pile should be empty. deck pile + current hand 
  // should be equal to the discard pile before drawCard functio is called
  printf("Beging testing drawCard() function. Case 1. ----------------------\n");
  // empty the deck
  int i = 0;
  int deckCount = G.deckCount[currentPlayer];
  for (; i<deckCount; ++i){
    G.deck[currentPlayer][i]=-1;
    G.deckCount[currentPlayer]--;
  } 
  //printGameState(&G, currentPlayer);
  // copy a gameState from the original gameState
  memcpy(&testG, &G, sizeof(struct gameState));

  drawCard(currentPlayer, &testG); 
  //printGameState(&testG, currentPlayer);

  printf("testG.handcount = %d, expected = %d: ", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]+1); 

  printf("Testing that the hand card pile is the same after removing the newly added card: ");
  int* newHandArray = removeElementFromArray(testG.hand[currentPlayer], testG.handCount[currentPlayer], testG.handCount[currentPlayer]-1);
  asserttrue(isSameArray(G.hand[currentPlayer], newHandArray, G.handCount[currentPlayer]));
  free(newHandArray);

  printf("testG.deckCount = %d, expected = %d: ", testG.deckCount[currentPlayer], G.discardCount[currentPlayer]-1); 
  asserttrue(testG.deckCount[currentPlayer] == G.discardCount[currentPlayer]-1); 

  printf("Testing that the newly added hand + current deck = old discard pile:  ");
  int handVal = testG.hand[currentPlayer][testG.handCount[currentPlayer]-1];
  int* newdeckArray = addElementToArray(testG.deck[currentPlayer], testG.deckCount[currentPlayer], handVal);
  asserttrue(isSameArray(G.discard[currentPlayer], newdeckArray, G.discardCount[currentPlayer]));
  free(newdeckArray);

  printf("testG.discardCount[currentPlayer] = %d, expected = %d: ", testG.discardCount[currentPlayer], 0); 
  asserttrue(testG.discardCount[currentPlayer] == 0); 

  // test case 2: when the deck is not empty:
  
  printf("Beging testing drawCard() function. Case 2. ----------------------\n");
  memset(&G, 23, sizeof(struct gameState));
  memset(&testG, 23, sizeof(struct gameState));
  initializeGame(numPlayers, kingdom, seed, &G); 
  // populating the deck pile
  j = 10;
  while(j>0){
    int rand = floor(Random()*10);
    G.deck[currentPlayer][G.deckCount[currentPlayer]]= kingdom[rand];
    G.deckCount[currentPlayer]++;
    j--;
  }

  // populating the discard pile
  j = 5;
  while(j>0){
    int rand = floor(Random()*10);
    G.discard[currentPlayer][G.discardCount[currentPlayer]]= kingdom[rand];
    G.discardCount[currentPlayer]++;
    j--;
  }
  memcpy(&testG, &G, sizeof(struct gameState));
  drawCard(currentPlayer, &testG); 
  //printGameState(&G, currentPlayer);
  //printGameState(&testG, currentPlayer);
 
    
  printf("testG.handcount = %d, expected = %d: ", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1); 
  asserttrue(testG.handCount[currentPlayer] == G.handCount[currentPlayer]+1); 

  printf("Testing that the hand card pile is the same after removing the newly added card: ");
  newHandArray = removeElementFromArray(testG.hand[currentPlayer], testG.handCount[currentPlayer], testG.handCount[currentPlayer]-1);
  asserttrue(isSameArray(G.hand[currentPlayer], newHandArray, G.handCount[currentPlayer]));
  free(newHandArray);

  printf("Testing that the last element of the new hand is the same as the last element of the old deck:  ");
  asserttrue(testG.hand[currentPlayer][testG.handCount[currentPlayer]-1] == G.deck[currentPlayer][G.deckCount[currentPlayer]-1]); 

  printf("testG.deckCount = %d, expected = %d: ", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]-1); 
  asserttrue(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]-1); 

  printf("Testing that the after removing the last element of the old deck is the same as the new deck: ");
  newdeckArray = removeElementFromArray(G.deck[currentPlayer], G.deckCount[currentPlayer], G.deckCount[currentPlayer]-1);
  asserttrue(isSameArray(testG.deck[currentPlayer], newdeckArray, testG.deckCount[currentPlayer]));

  printf("testG.discardCount = %d, expected = %d: ", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]); 
  asserttrue(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer]); 

  printf("Testing that the discard pile is the same before and after the drawCard operation: "); 
  asserttrue(isSameArray(G.discard[currentPlayer], testG.discard[currentPlayer], G.discardCount[currentPlayer]));

  printf("End of testing drawCard() function.----------------------\n"); 
  printf("\n\n"); 
  return 0;
}
