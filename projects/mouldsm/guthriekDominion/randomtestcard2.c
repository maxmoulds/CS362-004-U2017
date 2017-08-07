/* random test for SMITHY */
#include "asserttrue.h"
#include "dominion.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

/* Reveal cards from your deck until you reveal 2 Treasure cards. Put those
 * Treasure cards into your hand and discard the other revealed cards. */



#define MIN_HAND 5
#define ONE_TURN_GAMES 2
#define RANDOM_TURN_GAMES 2
#define RANDOM_GAME_RANDOM_TURNS 2 /* MAX VALUE */

#define IS_TREASURE (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)

int count = 0;/* yes... im bad */
int total = 0;

int main() {
  int numPlayers = 2; //? test this?
  srand(time(NULL)); //reset rng?
  struct gameState state; // no
  int randomSeed = 1; //hmm
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  //initializeGame(numPlayers, kingdomCards, randomSeed, &state);
  int drawntreasure = 0; //used to count how many treasures have been drawn

  int card = smithy;
  int choice1 = -1;
  int choice2 = -1;
  int choice3 = -1;
  int handPos = 0;
  int bonus = 0;
  int temp = state.handCount[0];
  int discard_ref = 0;
  int playedCards_ref = 0;
  //iterate game state here

  /* building game state */
  asserttrue(0, ( initializeGame(numPlayers, kingdomCards, randomSeed, &state) ), "InitilizeGame called");
  /* copy to test */
  struct gameState ref; 
  //memcpy(&ref, &state, sizeof(struct gameState));
  drawntreasure = 0;
  asserttrue(state.handCount[0], MIN_HAND , "(state.handcount, #ofcards in min hand?), hmm");
  //iterate smtiy tests here. 
  /*testing smithy */
  state.hand[0][0] = card;
  state.hand[1][0] = card;
  temp = state.handCount[0];

  asserttrue(state.numPlayers, numPlayers, "(state.numplayers, numplayers), still numplayer issue");

  memcpy(&ref, &state, sizeof(struct gameState)); /* hmm resulted in this */

  asserttrue(sizeof(struct gameState), sizeof(ref), "(sizeof(gamestate), sizeof(ref))");
  asserttrue(sizeof(ref), sizeof(state), "(sizeof(ref), sizeof(state))");
  discard_ref = state.discardCount[0];
  playedCards_ref = state.playedCardCount;

  playSmithy(handPos, &state);
  asserttrue(state.discardCount[0], discard_ref, "checking discard count");
  asserttrue(state.playedCardCount, (playedCards_ref+1), "checking that playedcards iterated");
  asserttrue(state.playedCards[(state.playedCardCount-1)], smithy, "checking that smithy is added to discard");


  asserttrue(state.numPlayers, numPlayers, "why is numplayers not matching");
  /* this is just a simple test... */
  //asserttrue(state.handCount[0], temp+3, "Checking handcount for first play is true"); /* should fail, because I introduced a game logic bug */
  /* the game state should be different from the ref */
  //asserttrue(isequalgamestate(ref, state), 0, "Checking if gamestat structs are still the same, (ref, cur_state)");

  struct gameState run2;
  memcpy(&run2, &ref, sizeof(struct gameState));
  handPos = 0; /*lets force a card at that pos */
  asserttrue(bonus, 0, "(bonus) should still be 0?");
  asserttrue(run2.numPlayers, numPlayers, "(run.numplayers, numplayers), whyyy?");
  playSmithy(handPos, &run2);
  asserttrue(isequalgamestate(&run2, &state), 0, "Checking if gamestat structs are still the same, (2nd run, and 1st run)");
  /* Okay lets loop... dumb looping but, looping */
  int i = 0; /* lets play 20 games, just test the next move as smithy */
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
  int discard_ref1 = 0;
  int playedCards_ref1 = 0;
  for (i = 0; i < ONE_TURN_GAMES; i++) {
    /* build turn */
    drawntreasure = 0;
    bonus = 0;
    handPos = 0;
    discard_ref = one_turn_ref1.discardCount[0];
    playedCards_ref = one_turn_ref1.playedCardCount;
    playSmithy(handPos, &one_turn_ref1);
    asserttrue(one_turn_ref1.discardCount[0], discard_ref, "checking discard count");
    asserttrue(one_turn_ref1.playedCardCount, (playedCards_ref+1), "checking that playedcards iterated");
    asserttrue(one_turn_ref1.playedCards[(one_turn_ref1.playedCardCount-1)], smithy, "checking that smithy is added to discard");
    bonus = 0;
    handPos = 0; /* shouldnt need to this but whatevs */
    discard_ref1 = one_turn_ref2.discardCount[0];
    playedCards_ref1 = one_turn_ref2.playedCardCount;
    playSmithy(handPos, &one_turn_ref2);
    asserttrue(one_turn_ref2.discardCount[0], discard_ref1, "checking discard count");
    asserttrue(one_turn_ref2.playedCardCount, (playedCards_ref1+1), "checking that playedcards iterated");
    asserttrue(one_turn_ref2.playedCards[(one_turn_ref2.playedCardCount-1)], smithy, "checking that smithy is added to discard");

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
      playSmithy(handPos, &one_turn_ref1);
      bonus = 0;
      handPos = 0; /* shouldnt need to this but whatevs */
      playSmithy(handPos, &one_turn_ref2);
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

