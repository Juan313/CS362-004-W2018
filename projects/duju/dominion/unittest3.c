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
  struct gameState G;
  memset(&G, 23, sizeof(struct gameState));
  int seed = 1000;
  int* kingdom = kingdomCards(smithy, adventurer, mine, village, feast, gardens,baron, steward, tribute, cutpurse);
  initializeGame(numPlayers, kingdom, seed, &G); 

  // testing the initial game setup
  printf("testing the initial game setup.\n ");
  int i = 0;
  for (; i<numPlayers; ++i){
    printf("player %d's score = %d, expected = %d:", i, scoreFor(i, &G), 3); 
    asserttrue(scoreFor(i, &G) == 3); 
  }
  
  // test that score of hand pile is calculated correctly
  printf("test that score of hand pile is calculated correctly: ");
  int currentPlayer = 0;
  clearHandPile(&G, currentPlayer);
  clearDeckPile(&G, currentPlayer);
  clearDiscardPile(&G, currentPlayer);
  i =0 ;
  for (; i<25; ++i) 
  {
    G.hand[currentPlayer][i] = curse;
    G.handCount[currentPlayer]++;
  }
  printf("player's score = %d, expected = %d:", scoreFor(currentPlayer, &G), -25); 
  asserttrue(scoreFor(currentPlayer, &G) == -25); 

  // test that score of deck pile is calculated correctly
  printf("test that score of deck pile is calculated correctly: ");
  clearHandPile(&G, currentPlayer);
  clearDeckPile(&G, currentPlayer);
  clearDiscardPile(&G, currentPlayer);
  i =0 ;
  for (; i<20; ++i) 
  {
    G.deck[currentPlayer][i] = estate;
    G.deckCount[currentPlayer]++;
  }
  printf("player's score = %d, expected = %d:", scoreFor(currentPlayer, &G), 20); 
  asserttrue(scoreFor(currentPlayer, &G) == 20); 

  // test that score of discard pile is calculated correctly
  printf("test that score of discard pile is calculated correctly: ");
  clearHandPile(&G, currentPlayer);
  clearDeckPile(&G, currentPlayer);
  clearDiscardPile(&G, currentPlayer);
  i =0 ;
  for (; i<15; ++i) 
  {
    G.discard[currentPlayer][i] = duchy;
    G.discardCount[currentPlayer]++;
  }
  printf("player's score = %d, expected = %d:", scoreFor(currentPlayer, &G), 45); 
  asserttrue(scoreFor(currentPlayer, &G) == 45); 

  // test that score of province card is calculated correctly
  printf("test that score of province card is calculated correctly: ");
  clearHandPile(&G, currentPlayer);
  clearDeckPile(&G, currentPlayer);
  clearDiscardPile(&G, currentPlayer);
  G.hand[currentPlayer][0] = province;
  G.handCount[currentPlayer]++;
  G.deck[currentPlayer][0] = province;
  G.deckCount[currentPlayer]++;
  G.discard[currentPlayer][0] = province;
  G.discardCount[currentPlayer]++;
  printf("player's score = %d, expected = %d:", scoreFor(currentPlayer, &G), 18); 
  asserttrue(scoreFor(currentPlayer, &G) == 18); 

  // test that score of great_hall card is calculated correctly
  printf("test that score of great_hall card is calculated correctly: ");
  clearHandPile(&G, currentPlayer);
  clearDeckPile(&G, currentPlayer);
  clearDiscardPile(&G, currentPlayer);
  G.hand[currentPlayer][0] = great_hall;
  G.handCount[currentPlayer]++;
  G.deck[currentPlayer][0] = great_hall;
  G.deckCount[currentPlayer]++;
  G.discard[currentPlayer][0] = great_hall;
  G.discardCount[currentPlayer]++;
  printf("player's score = %d, expected = %d:", scoreFor(currentPlayer, &G), 3); 
  asserttrue(scoreFor(currentPlayer, &G) == 3); 

  // test that score of garden card is calculated correctly
  printf("test that score of garden card is calculated correctly: ");
  clearHandPile(&G, currentPlayer);
  clearDeckPile(&G, currentPlayer);
  clearDiscardPile(&G, currentPlayer);
  i = 0;
  for (; i<20; ++i){
    G.hand[currentPlayer][i] = gardens;
    G.handCount[currentPlayer]++;
  }
  i = 0;
  for (; i<12; ++i){
    G.deck[currentPlayer][i] = gardens;
    G.deckCount[currentPlayer]++;
  }
  i = 0;
  for (; i<17; ++i){
    G.discard[currentPlayer][i] = gardens;
    G.discardCount[currentPlayer]++;
  }
  printf("player's score = %d, expected = %d:", scoreFor(currentPlayer, &G), 4); 
  asserttrue(scoreFor(currentPlayer, &G) == 4); 

  return 0;
}
