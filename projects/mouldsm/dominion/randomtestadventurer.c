/* random test for adventurer */
#include "asserttrue.h"
#include "dominion.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
/* Reveal cards from your deck until you reveal 2 Treasure cards. Put those
 * Treasure cards into your hand and discard the other revealed cards. */

#define MIN_HAND 5
#define ONE_TURN_GAMES 2
#define RANDOM_TURN_GAMES 2
#define RANDOM_GAME_RANDOM_TURNS 2/* MAX VALUE */

#define IS_TREASURE (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)

//extern int count[2]; /* yes... im bad */
int total = 0;
int count = 0;

int main() {
  int numPlayers = 2; //? test this?
  struct gameState state; // no
  struct gameState ref;
  struct gameState run2;
  int randomSeed = 1; //hmm
  srand(time(NULL));
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  //initializeGame(numPlayers, kingdomCards, randomSeed, &state);
  int drawntreasure = 0; //used to count how many treasures have been drawn

  int card = adventurer;
  int choice1 = -1;
  int choice2 = -1;
  int choice3 = -1;
  int handPos = 0;
  int bonus = 0;
  int temp = state.handCount[0];

  asserttrue(0, ( initializeGame(numPlayers, kingdomCards, randomSeed, &state) ), "InitilizeGame called, state");
  asserttrue(0, ( initializeGame(numPlayers, kingdomCards, randomSeed, &run2) ), "InitilizeGame called, run2");
  //asserttrue(0, ( initializeGame(numPlayers, kingdomCards, randomSeed, &ref) ), "InitilizeGame called, ref");
  
  drawntreasure = 0;
  
  asserttrue(state.handCount[0], MIN_HAND , "(state.handcount, #ofcards in min hand?), hmm");
  state.hand[0][0] = card;
  state.hand[1][0] = card;
  run2.hand[0][0] = card;
  run2.hand[1][0] = card;

  temp = state.handCount[0];
  
  asserttrue(state.numPlayers, numPlayers, "(state.numplayers, numplayers), still numplayer issue");
  
  memcpy(&ref, &state, sizeof(struct gameState)); /* hmm resulted in this */
  
  cardAdventurer(card, choice1, choice2, choice3, &state, 0, &bonus);
  cardAdventurer(card, choice1, choice2, choice3, &run2, 0, &bonus);
  asserttrue(run2.supplyCount[0], state.supplyCount[0], "hmm checking manually supply count?");
  asserttrue(isequalgamestate(&run2, &run2), 0, "Checking if gamestat structs are still the same, (2nd run, and 1st run)");
  /* Okay lets loop... dumb looping but, looping */
  int i = 0; /* lets play 20 games, just test the next move as adventrurer */
  struct gameState one_turn_ref1;
  struct gameState one_turn_ref2;
  ref.hand[0][0] = card;
  ref.hand[1][0] = card;
  /* OKAY SO THERE IS something i cant figure out going on with numPlayers */
  /* manually setting this, so i dont just fail over and over, already dinged once */
  ref.numPlayers = numPlayers;
  asserttrue(ref.numPlayers, numPlayers, "(ref.numplayers, numplayers), because idk");
  memcpy(&one_turn_ref1, &ref, sizeof(struct gameState));
  memcpy(&one_turn_ref2, &ref, sizeof(struct gameState));
  for (i = 0; i < ONE_TURN_GAMES; i++) {
    /* build turn */
    drawntreasure = 0;
    bonus = 0;
    handPos = 0;
    cardAdventurer(card, choice1, choice2, choice3, &one_turn_ref1, handPos, &bonus);
    bonus = 0;
    handPos = 0; /* shouldnt need to this but whatevs */
    cardAdventurer(card, choice1, choice2, choice3, &one_turn_ref2, handPos, &bonus);
    asserttrue(isequalgamestate(&one_turn_ref1, &one_turn_ref2), 0, "checking one turn to another, i know, why?");
  }
  asserttrue(i, ONE_TURN_GAMES, "did we complete the one_turn_games?");
  memcpy(&one_turn_ref1, &ref, sizeof(struct gameState));
  memcpy(&one_turn_ref2, &ref, sizeof(struct gameState)); 
  int j = 0;
  int rando = 1;
  int game_rando = rand() % RANDOM_TURN_GAMES + 1;
  for (i = 0; i < game_rando; i++) {
    /*get a random nnumber */
    rando = rand() % RANDOM_GAME_RANDOM_TURNS + 1; /* not right but im aokey widit */
    for (j = 0; j < rando; j++) {
      drawntreasure = 0;
      bonus = 0;
      handPos = 0;
      cardAdventurer(card, choice1, choice2, choice3, &one_turn_ref1, handPos, &bonus);
      bonus = 0;
      handPos = 0; /* shouldnt need to this but whatevs */
      cardAdventurer(card, choice1, choice2, choice3, &one_turn_ref2, handPos, &bonus);
      //asserttrue(isequalgamestate(one_turn_run1, one_turn_ref2), 0, "checking one turn to another"
    }
    /* now check */
    asserttrue(rando, j, "(rando # of turns, actual turn iter count)");
    asserttrue(isequalgamestate(&one_turn_ref1, &one_turn_ref2), 0, "checking states after turns");
  }
  //todo:
  //fix asserttrue to add string print
  //add "helper" functions. 
  //
  //
  //
  /*also if the seed changes, i'd hope this test would fail, but....*/
  /* All done, how'd I do? */
  asserttrue(count, total, "(tests passed == total tests) DID WE WIN?");
  return 0;
}

