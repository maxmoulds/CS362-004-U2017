#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"

int asserttrue(int a, int b, char * str) {
  if (a != b) {
    printf("TEST %d FAILED %d != %d :: %s\n", count[1]+1, a, b, str);
    count[1] += 1;
    return -1;
  }
  else if (a == b) {
    printf("TEST %d SUCCESSFULLY PASSED %d == %d :: %s\n", count[1]+1, a, b, str);
    count[0] += 1;
    count[1] += 1;
    return 0;
  } 
  else {
    printf("TEST %d FAILED ERR :: %s\n", count[1]+1, str);
    return -2;
  }
}

int isequalgamestate(struct gameState *one, struct gameState *two) {
  if (one == NULL || two == NULL) {
    return -1;
  }
  if (asserttrue(one->numPlayers, two->numPlayers, "Number of players (in isequal)") == 0) {
    return -1;
  }
  int i = 0;
  int ret = -1;
  for (i = 0, ret = 0; i < treasure_map+1; i++) {;
    if (asserttrue(one->supplyCount[i], two->supplyCount[i], "(num of cards in deck) testing supply count") == 0) {
      asserttrue(one->supplyCount[i], two->supplyCount[i], CARD_STRING[i]); 
    }
    else {
      asserttrue(one->supplyCount[i], two->supplyCount[i], CARD_STRING[i]);
      ret = -1;
    }
    if (asserttrue(one->embargoTokens[i], two->embargoTokens[i], "(embargo num of tokens) testing") == 0) {
      asserttrue(one->embargoTokens[i], two->embargoTokens[i], CARD_STRING[i]); 
    }   
    else {
      asserttrue(one->embargoTokens[i], two->embargoTokens[i], CARD_STRING[i]);
      ret = -1; 
    }
  }
  if (asserttrue(one->outpostPlayed, two->outpostPlayed, "outposts played") != 0) {
    ret = -1; 
  }
  if (asserttrue(one->outpostTurn, two->outpostTurn, "outpost turn") != 0) {
    ret = -1; 
  }
  if (asserttrue(one->whoseTurn, two->whoseTurn, "Whose turn?") != 0) {
    ret = -1; 
  }
  if (asserttrue(one->phase, two->phase, "Phase") != 0) {
    ret = -1; 
  }
  if (asserttrue(one->numActions, two->numActions, "NumActions") != 0) {
    ret = -1; 
  }
  if (asserttrue(one->coins, two->coins, "coins") == 0) {
    return -1; 
  }
  else {
    return 0;
  }
  return -1;

}

