/* unit test for playCard function */
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
	int ret = 0;
	/*testing smithy */
	ret = playCard(handPos, choice1, choice2, choice3, &state);
	asserttrue(state.numActions, temp);
	asserttrue(state.deck[0][handPos], smithy);
	state.deck[0][handPos] = estate;
	int nextCard = state.deck[0][handPos];
	int nexterCard = state.deck[0][handPos]; 
	ret = playCard(handPos, choice1, choice2, choice3, &state);
	asserttrue(state.deck[0][handPos], estate);
	asserttrue(state.deck[0][handPos], nextCard);
	asserttrue(nextCard, nexterCard);
	/*asserttrue(state.deck[0][4], smithy); */

}

