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
  printf("testing the count of copper: ");
  int currentPlayer = 2;
  printf("fullDeckCount = %d, expected = %d:", fullDeckCount(currentPlayer, copper, &G), 7); 
  asserttrue(fullDeckCount(currentPlayer, copper,&G) == 7); 

  printf("testing the count of estate: ");
  currentPlayer = 1;
  printf("fullDeckCount = %d, expected = %d:", fullDeckCount(currentPlayer, estate, &G), 3); 
  asserttrue(fullDeckCount(currentPlayer, estate,&G) == 3); 
 
  int rand = floor(Random()*10);
  int card1 = kingdom[rand]; 
  rand = floor(Random()*10);
  int card2 = kingdom[rand]; 
  rand = floor(Random()*10);
  int card3 = kingdom[rand]; 
  int j = 10; 
  while(j>0){
    G.hand[currentPlayer][G.handCount[currentPlayer]]= card1;
    G.handCount[currentPlayer]++;
    j--;
  }
  j = 20; 
  while(j>0){
    G.deck[currentPlayer][G.deckCount[currentPlayer]]= card2;
    G.deckCount[currentPlayer]++;
    j--;
  }
  j = 15;
  while(j>0){
    G.discard[currentPlayer][G.discardCount[currentPlayer]]= card3;
    G.discardCount[currentPlayer]++;
    j--;
  }
  printf("testing the count of randomly generated card1: ");
  printf("fullDeckCount = %d, expected = %d:", fullDeckCount(currentPlayer, card1, &G), 10); 
  asserttrue(fullDeckCount(currentPlayer,card1,&G) == 10); 

  printf("testing the count of randomly generated card2: ");
  printf("fullDeckCount = %d, expected = %d:", fullDeckCount(currentPlayer, card2, &G), 20); 
  asserttrue(fullDeckCount(currentPlayer,card2,&G) == 20); 

  printf("testing the count of randomly generated card3: ");
  printf("fullDeckCount = %d, expected = %d:", fullDeckCount(currentPlayer, card3, &G), 15); 
  asserttrue(fullDeckCount(currentPlayer,card3,&G) == 15); 
 
  return 0;
}
