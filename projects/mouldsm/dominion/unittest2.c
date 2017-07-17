/* unit test for shuffle */
#include "asserttrue.h"
#include "dominion.h"

int main() {

	int numPlayers = 2;
	struct gameState state;
	int randomSeed = 1;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);
	int card = state.deck[0][5];
	shuffle(0, &state);
	if (state.deck[0][3] == card) {
		asserttrue(1,0);
		/*asserttrue(state.deck[0][5], card);*/
	/* Note to self: there is something odd about how this shuffles...*/
	}
	else {
		asserttrue(0,0);
	}
}

