/* unit test for smithy */
#include "asserttrue.h"
#include "dominion.h"

int main() {

	int numPlayers = 2;
	struct gameState state;
	int randomSeed = 1;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);
	
	int card = smithy;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int bonus = 0;
	int temp = state.handCount[0];

	/*testing smithy */
	cardSmithy(card, choice1, choice2, choice3, &state, handPos, &bonus);
	asserttrue(state.handCount[0], temp+3); /* should fail, because I introduced a game logic bug */

}

