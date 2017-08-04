#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_helpers.h"
#include "dominion.h"
#include "dominion_helpers.h"

void testGainCard(void);
void printTestCase(int card, int supplyCase, int toFlag);

int main(int argv, char **argc) {
    testGainCard();
    return 0;
}

void testGainCard(void) {
    int seed = 1, numPlayers = 2;
    struct gameState testState, expectedState, cleanState;
    // These cards are arbitrarily chosen
    int kingdomCards[10] = { smithy, adventurer, village, mine, council_room,
        cutpurse, outpost, minion, steward, embargo };

    int card = 0;
    int discardCount = 0, deckCount = 0, handCount = 0;

    // Create blank game state
    initializeGame(numPlayers, kingdomCards, seed, &testState);
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    int player = whoseTurn(&cleanState);

    // Test the chosen card types...
    for (int cardNum = 0; cardNum < 10; ++cardNum) {

        card = kingdomCards[cardNum];

        // With empty and non-empty supply...
        for (int supplyCase = 0; supplyCase <= 1; ++supplyCase) {

            if (supplyCase) { // non-empty supply
                testState.supplyCount[card] = 1;         
                // Expected state should remove a card
                expectedState.supplyCount[card] = 0;
            } else { // empty supply
                // Expected state will remain the same
                testState.supplyCount[card] = 0;
                expectedState.supplyCount[card] = 0;
            }

            // Gain card to deck, hand, and discard...
            for (int toFlag = 0; toFlag <= 2; ++toFlag) {

                // Only need to set expected state if it's possible to grab a card
                if (supplyCase) {
                    switch (toFlag) {
                        case 0: // add to discard
                            discardCount = expectedState.discardCount[player];
                            expectedState.discard[player][discardCount] = card;
                            expectedState.discardCount[player]++;
                            break;
                        case 1: // add to deck
                            deckCount = expectedState.deckCount[player];
                            expectedState.deck[player][deckCount] = card;
                            expectedState.deckCount[player]++;
                            break;
                        case 2: // add to hand
                            handCount = expectedState.handCount[player];
                            expectedState.hand[player][handCount] = card;
                            expectedState.handCount[player]++;
                            break;
                    }
                }

                // Copy test state to clean state
                memcpy(&cleanState, &testState, sizeof(struct gameState));

                // Attempt gainCard
                gainCard(card, &testState, toFlag, player);

                // Check resulting state
                printTestCase(card, supplyCase, toFlag);

                assert_print(expectedState.discardCount[player] == testState.discardCount[player]);
                printf(": Test first player discard count\n");

                assert_print(expectedState.deckCount[player] == testState.deckCount[player]);
                printf(": Test first player deck count\n");

                assert_print(expectedState.handCount[player] == testState.handCount[player]);
                printf(": Test first player hand count\n");

                assert_print(expectedState.discardCount[player+1] == testState.discardCount[player+1]);
                printf(": Test second player discard count\n");

                assert_print(expectedState.deckCount[player+1] == testState.deckCount[player+1]);
                printf(": Test second player deck count\n");

                assert_print(expectedState.handCount[player+1] == testState.handCount[player+1]);
                printf(": Test second player hand count\n");


                printf("\n");

                // Reset state
                memcpy(&testState,     &cleanState, sizeof(struct gameState));
                memcpy(&expectedState, &cleanState, sizeof(struct gameState));
            }
        }
    }
}

void printTestCase(int card, int supplyCase, int toFlag) {
    printf("TEST CASE: Card #%d, ", card);
    if (supplyCase) {
        printf("non-empty supply, ");
    } else {
        printf("empty supply, ");
    }

    switch (toFlag) {
        case 0:
            printf(" card to discard.\n");
            break;
        case 1:
            printf(" card to deck.\n");
            break;
        case 2:
            printf(" card to hand.\n");
            break;
    }
}
