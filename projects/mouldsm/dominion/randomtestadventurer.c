/* random test for adventurer */
#include "asserttrue.h"
#include "dominion.h"

/* Reveal cards from your deck until you reveal 2 Treasure cards. Put those
 * Treasure cards into your hand and discard the other revealed cards. */

#define IS_TREASURE (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)

int main() {
	int numPlayers = 2; //? test this?
	struct gameState state; // no
	int randomSeed = 1; //hmm
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	
   initializeGame(numPlayers, kingdomCards, randomSeed, &state);
	
   int drawntreasure = 0; //used to count how many treasures have been drawn
   
	int card = adventurer;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int bonus = 0;
	int temp = state.handCount[0];

   //iterate game state here

   /* building game state */
   initializeGame(numPlayers, kingdomCards, randomSeed, &state);
   drawntreasure = 0;

   //iterate advernture tests here. 
	/*testing adventure */
	cardAdventurer(card, choice1, choice2, choice3, &state, handPos, &bonus);
	asserttrue(state.handCount[0], temp+3i); /* should fail, because I introduced a game logic bug */

   //todo:
   //fix asserttrue to add string print
   //add "helper" functions. 
   //
   //
   //
/*also if the seed changes, i'd hope this test would fail, but....*/
}

