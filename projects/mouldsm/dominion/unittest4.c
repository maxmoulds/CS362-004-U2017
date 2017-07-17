/* unit test for updateCoins function */
#include "asserttrue.h"
#include "dominion.h"

int updateCoins(int player, struct gameState *state, int bonus);

int main() {

	int numPlayers = 2;
	struct gameState state;
	int randomSeed = 1;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	int player = 0;
	int bonus = 1;
	int temp = state.coins;
	updateCoins(player, &state, bonus);
	asserttrue(state.coins,temp+bonus);
}

