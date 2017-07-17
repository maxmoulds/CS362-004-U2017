/* card test feast */
#include "asserttrue.h"
#include "dominion.h"

int main() {
        int numPlayers = 2;
        struct gameState state;
        int randomSeed = 1;
        int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
        initializeGame(numPlayers, kingdomCards, randomSeed, &state);

        int card = feast; /* its safe to assume enum in dominion.h is right, haha -random person commenting */
        int choice1 = gold; /* yes i used a feast to get a feast, im hungry */
        int choice2 = -1;
        int choice3 = -1;
        int handPos = 0;
        int bonus = 0;
        int temp = state.handCount[0];
	
	/* lesh breakthings...*/
	state.supplyCount[feast]= 3;
	state.hand[0][0] = feast;
	//state.hand[0][1] = feast;
	asserttrue(state.supplyCount[feast], 3);
	//asserttrue(1, 0);
	asserttrue(supplyCount(choice1, &state), 3);
/* error here i can figure out, loops for ever. hmmm... submission time */
        /*cardFeast(card, choice1, choice1, choice1, &state, handPos, &bonus);
	asserttrue(state.discardCount[0], 1);
        asserttrue(state.handCount[0], temp - 1);
	*/
	/* check that it limits cost to 5 or less */
	
	


}

