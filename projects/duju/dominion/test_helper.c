#include "test_helper.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


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

int* addElementToArray(int* originalArray,int size, int added){
  int* newArray = malloc((size+1)*sizeof(int));
  int i = 0;
  for (; i<size; ++i){
    newArray[i] = originalArray[i];
  }
  newArray[size] = added;
  return newArray;
}

void printGameState(struct gameState* G, int player){

   int i;
   printf("The player is %d\n", player); 
   //printf("The turn is %d\n", G->whoseTurn); 
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

  /*
   printf("playedcard count is: %d\n", G->playedCardCount); 
   printf("played card is: "); 
   for (i=0; i<G->playedCardCount; ++i){
     printf("%d\t", G->playedCards[i]); 
   }
   printf("\n");
   */
}
void asserttrue(bool statement){

  if (statement)
    printf("TEST SUCCESSFULLY COMPLETED!\n");
  else 
    printf("TEST FAILED!!!!!!!!!!!!!!!!!!!!!!!!!\n");
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

void clearHandPile(struct gameState* G, int player){
  int i = 0;
  for (; i< G->handCount[player]; ++i){
    G->hand[player][i] = -1;
  }
  G->handCount[player] = 0;
}

void clearDeckPile(struct gameState* G, int player){
  int i = 0;
  for (; i< G->deckCount[player]; ++i){
    G->deck[player][i] = -1;
  }
  G->deckCount[player] = 0;
}

void clearDiscardPile(struct gameState* G, int player){
  int i = 0;
  for (; i< G->discardCount[player]; ++i){
    G->discard[player][i] = -1;
  }
  G->discardCount[player] = 0;
}

void fillPile(struct gameState* G, int player, int flag, int *array, int size){
  // flag =0, fill the hand pile
  if (flag == 0) {
    clearHandPile(G, player);
    int i = 0;
    for (; i<size; ++i) {
      G->hand[player][i] = array[i];
      G->handCount[player]++;
    }
    return;
  } 
  // flag =1, fill the deck pile
  if (flag == 1) {
    clearDeckPile(G, player);
    int i = 0;
    for (; i<size; ++i) {
      G->deck[player][i] = array[i];
      G->deckCount[player]++;
    }
    return;
  } 
  // flag =2, fill the discard pile
  if (flag == 2) {
    clearDiscardPile(G, player);
    int i = 0;
    for (; i<size; ++i) {
      G->discard[player][i] = array[i];
      G->discardCount[player]++;
    }
    return;
  } 

}
