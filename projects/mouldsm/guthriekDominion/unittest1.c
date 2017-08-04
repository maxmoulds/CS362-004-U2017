#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_helpers.h"
#include "dominion.h"

void testBuyCard(void);
void printCaseTitle(int buyCase, int cardCase, int coinCase);

int main(int argv, char **argc) {
    testBuyCard();
    return 0;
}

void testBuyCard(void) {
    
    int seed = 1, numPlayers = 2;
    struct gameState testState, expectedState, cleanState;
    int kingdomCards[10] = { smithy, adventurer, village, mine, council_room,
        cutpurse, outpost, sea_hag, steward, embargo };

    // Create blank game state
    initializeGame(numPlayers, kingdomCards, seed, &testState);


    int player = whoseTurn(&cleanState);

    // Set buy / card / coin parameters based on test case number
    for (int buyCase = 1; buyCase <= 3; ++buyCase) {
        switch (buyCase) {
            case 1:
                testState.numBuys = 0;
                break;
            case 2:
                testState.numBuys = 1;
                break;
            case 3:
                testState.numBuys = 2;
                break;
        }

        // Will use "Village" card for buyCard tests
        for (int cardCase = 1; cardCase <= 3; ++cardCase) {
            switch (cardCase) {
                case 1:
                    testState.supplyCount[village] = 0;
                    break;
                case 2:
                    testState.supplyCount[village] = 1;
                    break;
                case 3:
                    testState.supplyCount[village] = 2;
                    break;
            }

            for (int coinCase = 1; coinCase <= 3; ++coinCase) {
                switch (coinCase) {
                    case 1:
                        testState.coins = 2;
                        break;
                    case 2:
                        testState.coins = 3;
                        break;
                    case 3:
                        testState.coins = 4;
                        break;
                }

                // Copy test state into clean & expected states
                memcpy(&cleanState,    &testState, sizeof(struct gameState));
                memcpy(&expectedState, &testState, sizeof(struct gameState));

                // Set expected state values based on test case
                if (buyCase > 1 && cardCase > 1 && coinCase > 1) {
                    // Number of buys should decrease by 1
                    expectedState.numBuys--;
                    // Village cost 3 coins, so coins should decrease by that amount
                    expectedState.coins -= 3;
                    // Supply count of village should decrease by 1
                    expectedState.supplyCount[village]--;
                    // Village should be added to the discard pile
                    expectedState.discard[player][expectedState.discardCount[player]] = village;
                    // Size of discard pile should increase by 1
                    expectedState.discardCount[player]++;
                }

                // Attempt to buy the Village card
                buyCard(village, &testState);
                
                // Test state against expected state
                printCaseTitle(buyCase, cardCase, coinCase);

                assert_print(expectedState.numBuys == testState.numBuys);
                printf(": Test number of buys available\n");

                assert_print(expectedState.coins == testState.coins);
                printf(": Test number of coins remaining\n");

                assert_print(expectedState.supplyCount[village] == testState.supplyCount[village]);
                printf(": Test supply count for Village card\n");

                int top = testState.discardCount[player] - 1;
                assert_print(expectedState.discard[player][top] == testState.discard[player][top]);
                printf(" Test card at top of discard pile\n");

                assert_print(expectedState.discardCount[player] == testState.discardCount[player]);
                printf(" Test number of cards in discard pile\n");

                printf("\n");

                // Reset test state
                memcpy(&testState, &cleanState, sizeof(struct gameState));
            }
        }
    }
}

void printCaseTitle(int buyCase, int cardCase, int coinCase) {
    printf("TEST CASE: ");

    // Print the buy case description
    switch (buyCase) {
        case 1:
            printf("numBuys = 1, ");
            break;
        case 2:
            printf("numBuys = 2, ");
            break;
        case 3:
            printf("numBuys = 3, ");
            break;
    }

    // Print the card case description
    switch (cardCase) {
        case 1:
            printf("0 cards in supply, ");
            break;
        case 2:
            printf("1 cards in supply, ");
            break;
        case 3:
            printf("2 cards in supply, ");
            break;
    }

    // Print the coin case description
    switch (coinCase) {
        case 1:
            printf("coins < cost.\n");
            break;
        case 2:
            printf("coins == cost.\n");
            break;
        case 3:
            printf("coins > cost.\n");
            break;
    }
}
