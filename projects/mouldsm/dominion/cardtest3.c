/* unit test for council_room */
#include "asserttrue.h"
#include "dominion.h"

int main() {

	int numPlayers = 2;
	struct gameState state;
	int randomSeed = 1;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);
	
	int card = council_room;
	int choice1 = -1;
	int choice2 = -1;
	int choice3 = -1;
	int handPos = 0;
	int bonus = 0;
	int temp = state.handCount[0];

	/*testing smithy */
	cardCouncilRoom(card, choice1, choice2, choice3, &state, handPos, &bonus);
	asserttrue(state.discardCount[0], 1);
	asserttrue(state.handCound[0], temp - 1); 
/*Sorry but someone put Fargo S03 on and Noah Hawley is just murdering my childhood innocence...*/
}

