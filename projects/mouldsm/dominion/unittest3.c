/* unit test for stub function */
#include "asserttrue.h"
#include "dominion.h"

int main() {

	int numPlayers = 2;
	struct gameState state;
	int randomSeed = 1;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);
	
	int handPos = 1; /* its the 2nd card in the hand? */
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	
	/* I am breaking stuff here. */
	state.phase = 0;
	state.numActions = 10;
	
	state.deck[0][handPos] = smithy;
	int temp = state.numActions;
	/*state.deck[0][handPos + 1] = adventurer; */

	/*testing smithy */
	playCard(handPos, choice1, choice2, choice3, &state);
	asserttrue(state.numActions, temp);

}

