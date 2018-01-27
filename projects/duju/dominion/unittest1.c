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

int cmp(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}
int* removeElementFromArray(int* originalArray,int size, int handPos){
  int* newArray = malloc((size-1)*sizeof(int)); 
  int i = 0;
  int j = 0;
  if (handPos >= size) return NULL;
  for (; i<size; ++i){
    if (i != handPos){
      newArray[j] = originalArray[i];
      ++j;
    }
  }
  return newArray;

}

void printGameState(struct gameState* G, int player){

   int i;
   printf("The player is %d\n", player); 
   printf("The turn is %d\n", G->whoseTurn); 
   printf("Handcounts: %d\n", G->handCount[player]); 
   printf("current hand is: "); 
   for (i=0; i<G->handCount[player]; ++i){
     printf(" %d\t", G->hand[player][i]); 
   }
   printf("\n");

   printf("Deckcounts: %d\n", G->deckCount[player]); 
   printf("current deck is: "); 
   for (i=0; i<G->deckCount[player]; ++i){
     printf("%d\t", G->deck[player][i]); 
   }
   printf("\n");

   printf("discardCounts: %d\n", G->discardCount[player]); 
   printf("current discard is: "); 
   for (i=0; i<G->discardCount[player]; ++i){
     printf("%d\t", G->discard[player][i]); 
   }
   printf("\n");

   printf("playedcard count is: %d\n", G->playedCardCount); 
   printf("played card is: "); 
   for (i=0; i<G->playedCardCount; ++i){
     printf("%d\t", G->playedCards[i]); 
   }
   printf("\n");
}

bool isSameArray(int* array1, int* array2, int size){
  qsort ((void*)(array1), size, sizeof(int), cmp); 
  qsort ((void*)(array2), size, sizeof(int), cmp); 
  int i = 0;
  for (; i<size; ++i){
    if (array1[i] != array2[i])
      return false;
  }
  return true;  
}

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
  int handPos = 6;
  int j = 10;
  while(j>0){
    int rand = floor(Random()*10);
    G.hand[currentPlayer][G.handCount[currentPlayer]]= kingdom[rand];
    G.handCount[currentPlayer]++;
    j--;
  }
  // copy a gameState from the original gameState
  
  memcpy(&testG, &G, sizeof(struct gameState));

  // run discardCard function on the original gameState
  // compare the gameState before and after discardCard function is run 
  // test case 1: if the card is trashed, the playedCardCount should increate by 1;
  // and the last element of playCards should be equal to the trashed card 
  printf("Beging testing discardCard() function. Case 1. ----------------------\n");
  discardCard(handPos, 0, &testG, 0); 

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
  discardCard(handPos, 0, &testG, 1); 

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
  return 0;
}
