/* unit test initialize game function */
#include "asserttrue.h"
#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

	asserttrue(0,0);

	int numPlayers = 2;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randomSeed = 1;
	struct gameState state;

/* 2 player game */
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);
	asserttrue(state.numPlayers, numPlayers);
	asserttrue(state.supplyCount[curse], 10);
        asserttrue(state.supplyCount[estate], 8);
        asserttrue(state.supplyCount[duchy], 8);
        asserttrue(state.supplyCount[province], 8);
        asserttrue(state.supplyCount[copper], 46);
        asserttrue(state.supplyCount[silver], 40);
        asserttrue(state.supplyCount[gold], 30);
        asserttrue(state.supplyCount[council_room], -1);
        asserttrue(state.supplyCount[feast], -1);
        asserttrue(state.supplyCount[gardens], 8);
        asserttrue(state.supplyCount[mine], 10);
        asserttrue(state.supplyCount[remodel], -1);
        asserttrue(state.supplyCount[smithy], 10);
        asserttrue(state.supplyCount[village], 10);
        asserttrue(state.supplyCount[baron], -1);
        asserttrue(state.supplyCount[great_hall], -1);
        asserttrue(state.supplyCount[minion], 10);
        asserttrue(state.supplyCount[steward], -1);
        asserttrue(state.supplyCount[tribute], 10);
        asserttrue(state.supplyCount[ambassador], -1);
        asserttrue(state.supplyCount[outpost], -1);
        asserttrue(state.supplyCount[salvager], -1);
        asserttrue(state.supplyCount[sea_hag], 10);
        asserttrue(state.supplyCount[treasure_map], -1);
	asserttrue(state.embargoTokens[0], 0);
	asserttrue(state.outpostPlayed, 0);
	asserttrue(state.outpostTurn, 0);
	asserttrue(state.whoseTurn, 0);
	asserttrue(state.phase, 0);
	asserttrue(state.numActions, 1);
	asserttrue(state.coins, 4);
	asserttrue(state.numBuys, 1);
	asserttrue(state.hand[0][0], 4);
	asserttrue(state.handCount[0], 5);
	asserttrue(state.deck[0][0], 1);
	asserttrue(state.deckCount[0], 5);
	asserttrue(state.discard[0][0], 0);
	asserttrue(state.discardCount[0], 0);
	asserttrue(state.playedCards, 0); /* error here? unintialized... */
	asserttrue(state.playedCardCount, 0);
}

