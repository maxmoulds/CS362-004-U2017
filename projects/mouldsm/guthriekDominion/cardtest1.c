#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_helpers.h"
#include "dominion.h"
#include "dominion_helpers.h"

void testPlaySmithy(void);
void runTestCases(struct gameState *expectedState, struct gameState *testState);

int main(int argv, char **argc) {
    testPlaySmithy();
    return 0;
}

void testPlaySmithy(void) {
    int seed = 1, numPlayers = 2;
    struct gameState testState, expectedState, cleanState;
    // These cards are arbitrarily chosen
    int kingdomCards[10] = { smithy, adventurer, village, mine, council_room,
        cutpurse, outpost, minion, steward, embargo };

    int handCount, deckCount, playedCardCount;

    // Create blank game state
    initializeGame(numPlayers, kingdomCards, seed, &testState);

    // Add Smithy card to player's hand
    int player = whoseTurn(&testState);
    int smithyPos = testState.handCount[player];
    testState.hand[player][smithyPos] = smithy;
    testState.handCount[player]++;

    memcpy(&expectedState, &testState, sizeof(struct gameState));
    memcpy(&cleanState,    &testState, sizeof(struct gameState));

    // Set expected state based on Smithy mechanics
    // Smithy should draw three cards and put them into the players hand

    /*
     *  CASE 1: More than 3 cards in deck
     */
    printf("Testing Smithy mechanics with more than 3 cards in deck.\n");
    for (int i = 0; i < 3; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Smithy should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][smithyPos];
    expectedState.playedCardCount++;
    // Replace Smithy with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][smithyPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playSmithy to set testState
    playSmithy(smithyPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));

    /*
     *  CASE 2: Exactly 3 cards in deck
     */
    printf("\nTesting Smithy mechanics with exactly 3 cards in deck.\n");

    // Set deck count to 3, discard count to 0
    player = 0;
    testState.deckCount[player] = 3;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Draw the 3 remaining cards
    for (int i = 0; i < 3; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Smithy should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][smithyPos];
    expectedState.playedCardCount++;
    // Replace Smithy with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][smithyPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playSmithy to set testState
    playSmithy(smithyPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    /*
     *  CASE 3: Less than 3 cards in deck, 0 in discard (not testing shuffle)
     */
    printf("\nTesting Smithy mechanics with less than 3 cards in deck.\n");
    
    // Set deck count to 2, discard count to 0
    player = 0;
    testState.deckCount[player] = 2;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Draw the 2 cards remaining in the deck
    for (int i = 0; i < 2; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Smithy should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][smithyPos];
    expectedState.playedCardCount++;
    // Replace Smithy with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][smithyPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playSmithy to set testState
    playSmithy(smithyPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));

    /*
     *  CASE 3: Less than 3 cards in deck, 0 in discard (not testing shuffle)
     */
    printf("\nTesting Smithy mechanics with 0 cards in deck.\n");
    
    // Set deck count to 0, discard count to 0
    player = 0;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Smithy should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][smithyPos];
    expectedState.playedCardCount++;
    // Replace Smithy with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][smithyPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playSmithy to set testState
    playSmithy(smithyPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset states
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
}

void runTestCases(struct gameState *expectedState, struct gameState *testState) {

    int player = whoseTurn(expectedState);
    int error = 0;

    // TEST: Hand count should have grown by 3
    assert_print(expectedState->handCount[player] == testState->handCount[player]);
    printf(": Hand count is correct (%d == %d)\n", expectedState->handCount[player],
        testState->handCount[player]);

    // TEST: Deck count should have decreased by 3
    assert_print(expectedState->deckCount[player] == testState->deckCount[player]);
    printf(": Deck count is correct (%d == %d)\n", expectedState->deckCount[player],
        testState->deckCount[player]);

    // TEST: Played cards count should have increased by 1
    assert_print(expectedState->playedCardCount == testState->playedCardCount);
    printf(": Played card count is correct (%d == %d)\n", expectedState->playedCardCount,
        testState->playedCardCount);

    // TEST: Discard count should not have changed
    assert_print(expectedState->discardCount[player] == testState->discardCount[player]);
    printf(": Discard count is correct (%d == %d)\n", expectedState->discardCount[player],
        testState->discardCount[player]);

    // TEST: Player hands should be identical
    error = 0;
    for (player = 0; player < expectedState->numPlayers; ++player) {
        for (int i = 0; i < expectedState->handCount[player]; ++i) {
            if (expectedState->hand[player][i] != testState->hand[player][i]) {
                error = 1;
            }
        }
    }
    assert_print(error == 0);
    printf(": Player hands contain correct cards\n");

    // TEST: Player decks should be identical
    error = 0;
    for (player = 0; player < expectedState->numPlayers; ++player) {
        for (int i = 0; i < expectedState->deckCount[player]; ++i) {
            if (expectedState->deck[player][i] != testState->deck[player][i]) {
                error = 1;
            }
        }
    }
    assert_print(error == 0);
    printf(": Player decks contain correct cards\n");

    // TEST: Played cards should be identical
    error = 0;
    for (int i = 0; i < expectedState->playedCardCount; ++i) {
        if (expectedState->playedCards[i] != testState->playedCards[i]) {
            error = 1;
        }
    }
    assert_print(error == 0);
    printf(": Played cards pile contains correct cards\n");

    // TEST: Player discards should be identical
    error = 0;
    for (player = 0; player < expectedState->numPlayers; ++player) {
        for (int i = 0; i < expectedState->discardCount[player]; ++i) {
            if (expectedState->discard[player][i] != testState->discard[player][i]) {
                error = 1;
            }
        }
    }
    assert_print(error == 0);
    printf(": Player discards contain correct cards\n");

    // TEST: Number of actions should not have changed
    assert_print(expectedState->numActions == testState->numActions);
    printf(": Number of actions is correct (%d == %d)\n", expectedState->numActions,
        testState->numActions);

    // TEST: Coins should be unchanged
    assert_print(expectedState->coins == testState->coins);
    printf(": Number of coins is correct (%d == %d)\n", expectedState->coins, testState->coins);

    // TEST: Number of buys should be unchanged
    assert_print(expectedState->numBuys == testState->numBuys);
    printf(": Number of buys is correct (%d == %d)\n", expectedState->numBuys, testState->numBuys);

}
