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


void testSmithy(int testCase, struct gameState* pre, struct gameState* post, int player, int handPos)
{
  bool result;
  if (pre->deckCount[player]<3){
    if (MY_DEBUG == 1) {
      printf("prepre??????????????????????????????????????????????????????????????\n");
      printGameState(pre,player); 
    }

    pre->handCount[player] = pre->handCount[player]+3;
    memcpy(pre->hand[player], post->hand[player], sizeof(int)*post->handCount[player]);
    pre->deckCount[player] = pre->discardCount[player] - (3 - pre->deckCount[player]);
    memcpy(pre->deck[player], post->deck[player], sizeof(int)*post->deckCount[player]);
    pre->discard[player][0]=pre->hand[player][handPos];
    int i = 1;
    for (; i<pre->discardCount[player]; ++i){
      pre->discard[player][i] = -1;
    }
    pre->discardCount[player] = 1;

    if (MY_DEBUG == 1) {
      printf("pre-----------------------------------------------------------------\n");
      printGameState(pre,player); 
      printf("post****************************************************************\n");
      printGameState(post,player); 
    }

    result = memcpy(pre, post, sizeof(struct gameState))==0;

    if (!result) {
      printf("Test Smithy card: case %d fail: Testing when deckCount is smaller than 3\n", testCase);
    }
  }
  else if (handPos == pre->handCount[player]-1){
    if (MY_DEBUG == 1) {
      printf("prepre??????????????????????????????????????????????????????????????\n");
      printGameState(pre,player); 
    }
    
    int discardCard = pre->hand[player][handPos];
    pre->hand[player][handPos] = pre->deck[player][pre->deckCount[player]-1];
    pre->hand[player][handPos+1] = pre->deck[player][pre->deckCount[player]-2];
    pre->hand[player][handPos+2] = pre->deck[player][pre->deckCount[player]-3];
    pre->handCount[player] = pre->handCount[player]+2;

    pre->deckCount[player] -= 3;

    pre->discard[player][pre->discardCount[player]] = discardCard; 
    pre->discardCount[player] += 1;
    if (MY_DEBUG == 1) {
      printf("pre-----------------------------------------------------------------\n");
      printGameState(pre,player); 
      printf("post****************************************************************\n");
      printGameState(post,player); 
    }
    bool result = memcpy(pre, post, sizeof(struct gameState))==0;

    if (!result) {
      printf("Test Smithy card: case %d fail: Testing when deckCount is greater than 3 and current Hand is the last card in the hand pile\n", testCase);
    }
  }
  else  {
    if (MY_DEBUG == 1) {
      printf("prepre??????????????????????????????????????????????????????????????\n");
      printGameState(pre,player); 
    }
    
    int discardCard = pre->hand[player][handPos];
    pre->hand[player][handPos] = pre->hand[player][pre->handCount[player]-1];
    pre->hand[player][pre->handCount[player]-1] = pre->deck[player][pre->deckCount[player]-1];
    pre->hand[player][pre->handCount[player]] = pre->deck[player][pre->deckCount[player]-2];
    pre->hand[player][pre->handCount[player]+1] = pre->deck[player][pre->deckCount[player]-3];
    pre->handCount[player] = pre->handCount[player]+2;

    pre->deckCount[player] -= 3;

    pre->discard[player][pre->discardCount[player]] = discardCard; 
    pre->discardCount[player] += 1;
    if (MY_DEBUG == 1) {
      printf("pre-----------------------------------------------------------------\n");
      printGameState(pre,player); 
      printf("post****************************************************************\n");
      printGameState(post,player); 
    }

    bool result = memcpy(pre, post, sizeof(struct gameState))==0;

    if (!result) {
      printf("Test Smithy card: case %d fail: Testing when deckCount is greater than 3 and current Hand is in the middle of the hand pile\n", testCase);
    }

  }

}


int main(){
  
  struct gameState pre, post;
  int randomTest;
  if (MY_DEBUG == 1){
    randomTest = 20;
  } else {
    randomTest = 10000;
  }
  int n;
  for (n=0; n<randomTest*.75; ++n) {
    int player = floor(Random()*MAX_PLAYERS);
    generateRandomGameState(&pre, player,false);
    memcpy(&post, &pre, sizeof(struct gameState));
    int handPos = floor(Random()*pre.handCount[player]);
    //printf("hand position is %d\n", handPos);
    cardEffectSmithy(player, &post, handPos);
    testSmithy(n, &pre, &post, player, handPos);
  } 

  
  return 0;
}
