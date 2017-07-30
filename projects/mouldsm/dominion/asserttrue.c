#include <stdio.h>
#include "asserttrue.h"
#include "dominion.h"

//extern int count[2];
char * CARD_STRING[] =
  {"curse",
   "estate",
   "duchy",
   "province",
   "copper",
   "silver",
   "gold",
   "adventurer",
   /* If no/only 1 treasure found, stop when full deck seen */
   "council_room",
   "feast", /* choice1 is supply # of card gained) */
   "gardens",
   "mine", /* choice1 is hand# of money to trash, choice2 is supply# of money to put in hand */
   "remodel", /* choice1 is hand# of card to remodel, choice2 is supply# */
   "smithy",
   "village",

   "baron", /* choice1: boolean for discard of estate */
   /* Discard is always of first (lowest index) estate */
   "great_hall",
   "minion", /* choice1:  1 = +2 coin, 2 = redraw */
   "steward", /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
   "tribute",

   "ambassador", /* choice1 = hand#, choice2 = number to return to supply */
   "cutpurse",
   "embargo", /* choice1 = supply# */
   "outpost",
   "salvager", /* choice1 = hand# to trash */
   "sea_hag",
   "treasure_map"
  }; 

int asserttrue(int a, int b, char * str) {
  if (a != b) {
    printf("TEST %d FAILED %d != %d :: %s\n", total+1, a, b, str);
    total += 1;
    return -1;
  }
  else if (a == b) {
    printf("TEST %d SUCCESSFULLY PASSED %d == %d :: %s\n", count+1, a, b, str);
    count += 1;
    total += 1;
    return 0;
  } 
  else {
    printf("TEST %d FAILED ERR :: %s\n", count+1, str);
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

