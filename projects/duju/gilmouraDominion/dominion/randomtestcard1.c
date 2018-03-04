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

int TreasureCardInDeck(struct gameState* g, int player){
  int i = 0;
  int sum = 0;
  for (; i<g->deckCount[player]; ++i){
    int card = g->deck[player][i];
    if (card == 4 || card == 5 || card == 6)
      sum += 1;
  }
  return sum;
}
int discardCardsInDeck(struct gameState* g, int player){
  int i = g->deckCount[player]-1;
  int num = 0;
  for ( ; i>=0; --i){
    int card = g->deck[player][i];
    if (card == 4 || card == 5 || card == 6)
      num += 1;
    if (num == 2)
      return g->deckCount[player]-i;
  }
  return -1;
}

void testAdventurer(int testCase, struct gameState* pre, struct gameState* post, int player, int handPos)
{
  if (TreasureCardInDeck(pre, player)>=2)
  {
    if (MY_DEBUG == 1) {
      printf("prepre??????????????????????????????????????????????????????????????\n");
      printGameState(pre,player); 
    }
    pre->handCount[player] += 1;
    int discardNum = discardCardsInDeck(pre,player); 
    pre->deckCount[player] -= discardNum; 
    pre->discardCount[player] += discardNum -1; 
    memcpy(pre->hand[player], post->hand[player], sizeof(int)*post->handCount[player]);
    memcpy(pre->discard[player], post->discard[player], sizeof(int)*post->discardCount[player]);
    if (MY_DEBUG == 1) {
      printf("pre-----------------------------------------------------------------\n");
      printGameState(pre,player); 
      printf("post****************************************************************\n");
      printGameState(post,player); 
    }
    bool result = memcpy(pre, post, sizeof(struct gameState))==0;

    if (!result) {
      printf("Test Adventurer card: case %d fail: when deck has more than two treasure cards\n", testCase);
    }
  }
  else {
    if (MY_DEBUG == 1) {
      printf("prepre??????????????????????????????????????????????????????????????\n");
      printGameState(pre,player); 
    }
    pre->handCount[player] += 1;
    pre->deckCount[player] = pre->discardCount[player]+pre->deckCount[player]-2; 
    pre->discardCount[player] = 1; 
    memcpy(pre->hand[player], post->hand[player], sizeof(int)*post->handCount[player]);
    memcpy(pre->deck[player], post->deck[player], sizeof(int)*post->deckCount[player]);
    memcpy(pre->discard[player], post->discard[player], sizeof(int)*post->discardCount[player]);
    if (MY_DEBUG == 1) {
      printf("pre-----------------------------------------------------------------\n");
      printGameState(pre,player); 
      printf("post****************************************************************\n");
      printGameState(post,player); 
    }
    bool result = memcpy(pre, post, sizeof(struct gameState))==0;

    if (!result) {
      printf("Test Adventurer card: case %d fail: when deck has less than two treasure cards\n", testCase);
    }
  }
    
}


int main(){
  
  struct gameState pre, post;
  int randomTest;
  if (MY_DEBUG  == 1){
    randomTest = 100;
  } else {
    randomTest = 10000;
  }
  int n;
  for (n=0; n<randomTest; ++n) {
    int player = floor(Random()*MAX_PLAYERS);
    generateRandomGameState(&pre, player, true);
    int r = floor(Random()*4);

    if (r == 0)
    {
      pre.deckCount[player] = 0;
      if (pre.discardCount[player] <= MAX_DECK - 2)
        pre.discardCount[player] += 2;
      pre.discard[player][pre.discardCount[player]-1] = floor(Random()*3) + copper;
      pre.discard[player][pre.discardCount[player]-2] = floor(Random()*3) + copper;
    }
    //printGameState(&pre,player); 
    memcpy(&post, &pre, sizeof(struct gameState));
    int handPos = floor(Random()*pre.handCount[player]);
    //printf("hand position is %d\n", handPos);
    int temphand[MAX_HAND];
    adventurerF(player, &post, temphand, 0, 0, 0);
    //cardEffectAdventurer(player, &post, handPos);
    //printGameState(&pre,player); 
    testAdventurer(n, &pre, &post, player, handPos);
    
  } 
  return 0;
}
