#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_helpers.h"
#include "dominion.h"
#include "dominion_helpers.h"

#define NUM_CARDS 27

void testGetCost(void);

int main(int argv, char **argc) {
    testGetCost();
    return 0;
}

void testGetCost(void) {
    // Hard code the cost of all 27 cards 
    int cardCost[NUM_CARDS];
    int cards[NUM_CARDS] = { curse, estate, duchy, province, copper, silver, gold, adventurer,
        council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall,
        minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag,
        treasure_map };

    // Source of card cost: http://wiki.dominionstrategy.com
    cardCost[curse] = 0;
    cardCost[estate] = 2;
    cardCost[duchy] = 5;
    cardCost[province] = 8;
    cardCost[copper] = 0;
    cardCost[silver] = 3;
    cardCost[gold] = 6;
    cardCost[adventurer] = 6;
    cardCost[council_room] = 5;
    cardCost[feast] = 4;
    cardCost[gardens] = 4;
    cardCost[mine] = 5;
    cardCost[remodel] = 4;
    cardCost[smithy] = 4;
    cardCost[village] = 3;
    cardCost[baron] = 4;
    cardCost[great_hall] = 3;
    cardCost[minion] = 5;
    cardCost[steward] = 3;
    cardCost[tribute] = 5;
    cardCost[ambassador] = 3;
    cardCost[cutpurse] = 4;
    cardCost[embargo] = 2;
    cardCost[outpost] = 5;
    cardCost[salvager] = 4;
    cardCost[sea_hag] = 4;
    cardCost[treasure_map] = 4;

    for (int i = 0; i < NUM_CARDS; ++i) {
        assert_print(cardCost[cards[i]] == getCost(cards[i])); 
        printf(": Cost of card #%d\n", cards[i]);
    }

    // Try two cards out of bounds, should return -1
    assert_print(-1 == getCost(-1));
    printf(": Negative numbered card (return -1)\n");
    assert_print(-1 == getCost(treasure_map+1));
    printf(": Out of range card (return -1)\n");
}
