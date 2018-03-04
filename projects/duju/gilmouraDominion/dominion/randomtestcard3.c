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


void testVillage(int testCase, struct gameState* pre, struct gameState* post, int player, int handPos)
{
  if (pre->deckCount[player] >= 1)
  {
    if (MY_DEBUG == 1) {
      printf("prepre??????????????????????????????????????????????????????????????\n");
      printGameState(pre,player); 
    }
    int card = pre->hand[player][handPos];
    pre->numActions += 2;
    pre->hand[player][handPos] = pre->deck[player][pre->deckCount[player]-1];
    pre->deckCount[player] -= 1;
    pre->discard[player][pre->discardCount[player]] = card; 
    pre->discardCount[player] += 1;
    if (MY_DEBUG == 1) {
      printf("pre-----------------------------------------------------------------\n");
      printGameState(pre,player); 
      printf("post****************************************************************\n");
      printGameState(post,player); 
    }
    bool result = memcpy(pre, post, sizeof(struct gameState))==0;

    if (!result) {
      printf("Test Village card: case %d fail: Testing when deckCount is greater than 1\n", testCase);
    }
  }
  else {
  
    if (MY_DEBUG == 1) {
      printf("prepre??????????????????????????????????????????????????????????????\n");
      printGameState(pre,player); 
    }
    pre->numActions += 2;
    memcpy(pre->hand[player], post->hand[player], sizeof(int)*post->handCount[player]);
    memcpy(pre->deck[player], post->deck[player], sizeof(int)*post->deckCount[player]);
    pre->deckCount[player] = pre->discardCount[player] - 1; 
    memcpy(pre->discard[player], post->discard[player], sizeof(int)*pre->discardCount[player]);
    pre->discardCount[player] = 1; 

    if (MY_DEBUG == 1) {
      printf("pre-----------------------------------------------------------------\n");
      printGameState(pre,player); 
      printf("post****************************************************************\n");
      printGameState(post,player); 
    }
    bool result = memcpy(pre, post, sizeof(struct gameState))==0;

    if (!result) {
      printf("Test Village card: case %d fail: Testing when deckCount is smaller than 1\n", testCase);
    }
  }
    
}


int main(){
  
  struct gameState pre, post;
  int randomTest;
  if (MY_DEBUG  == 1){
    randomTest = 20;
  } else {
    randomTest = 10000;
  }
  int n;
  for (n=0; n<randomTest; ++n) {
    int player = floor(Random()*MAX_PLAYERS);
    generateRandomGameState(&pre, player, true);
    //printGameState(&pre,player); 
    memcpy(&post, &pre, sizeof(struct gameState));
    int handPos = floor(Random()*pre.handCount[player]);
    //printf("hand position is %d\n", handPos);
    //cardEffectVillage(player, &post, handPos);
    villageF(player, &post, handPos);
    //printGameState(&pre,player); 
    testVillage(n, &pre, &post, player, handPos);
    
  } 
  return 0;
}
