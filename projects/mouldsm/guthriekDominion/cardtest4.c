#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_helpers.h"
#include "dominion.h"
#include "dominion_helpers.h"

void testPlayAdventurer(void);
void runTestCases(struct gameState *expectedState, struct gameState *testState);
void setTreasure(struct gameState *state, int numDeck, int numDiscard);
void drawTreasure(struct gameState *state);

int main(int argv, char **argc) {
    testPlayAdventurer();
    return 0;
}

void testPlayAdventurer(void) {
    int seed = 1, numPlayers = 2;
    struct gameState testState, expectedState, cleanState;
    // These cards are arbitrarily chosen
    int kingdomCards[10] = { adventurer, smithy, village, mine, council_room,
        cutpurse, outpost, minion, steward, embargo };

    int handCount, playedCardCount;

    // Create blank game state
    initializeGame(numPlayers, kingdomCards, seed, &testState);
    // Add Adventurer card to player's hand
    int player = whoseTurn(&testState);
    int adventurerPos = testState.handCount[player];
    testState.hand[player][adventurerPos] = adventurer;
    testState.handCount[player]++;

    memcpy(&expectedState, &testState, sizeof(struct gameState));
    memcpy(&cleanState,    &testState, sizeof(struct gameState));

    int caseCounter = 0;
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            caseCounter++;
            printf("\nCase %d -- %d deck treasure, %d discard treasure.\n",
                    caseCounter, i, j);

            // Fill deck/discard with treasure
            setTreasure(&testState, i, j); 
            memcpy(&expectedState, &testState, sizeof(struct gameState));

            // Adventurer should be placed in the played cards pile
            handCount = expectedState.handCount[player];
            playedCardCount = expectedState.playedCardCount;
            expectedState.playedCards[playedCardCount] = expectedState.hand[player][adventurerPos];
            expectedState.playedCardCount++;
            // Replace Adventurer with last card in hand
            expectedState.hand[player][adventurerPos] = expectedState.hand[player][handCount - 1];
            expectedState.handCount[player]--;

            // Run draw treasure mechanics
            drawTreasure(&expectedState);

            // Use playAdventurer to set testState
            playAdventurer(&testState);

            // Run test cases
            runTestCases(&expectedState, &testState);

            // Reset state
            memcpy(&testState,     &cleanState, sizeof(struct gameState));
            memcpy(&expectedState, &cleanState, sizeof(struct gameState));
        }
    }
}

void runTestCases(struct gameState *expectedState, struct gameState *testState) {

    int player = whoseTurn(expectedState);
    int error = 0;

    // TEST: Hand count should have grown by 2
    assert_print(expectedState->handCount[player] == testState->handCount[player]);
    printf(": Hand count is correct (%d == %d)\n", expectedState->handCount[player],
            testState->handCount[player]);

    // TEST: Deck count + discard count should have decreased by 2
    int expectedTotal = expectedState->deckCount[player] + expectedState->discardCount[player];
    int testTotal = testState->deckCount[player] + testState->discardCount[player];
    assert_print(expectedTotal == testTotal);
    printf(": Deck + discard count is correct (%d == %d)\n", expectedTotal, testTotal);

    // TEST: Played cards count should have increased by 1
    assert_print(expectedState->playedCardCount == testState->playedCardCount);
    printf(": Played card count is correct (%d == %d)\n", expectedState->playedCardCount,
            testState->playedCardCount);

    // TEST: Number of actions should not have changed
    assert_print(expectedState->numActions == testState->numActions);
    printf(": Number of actions is correct (%d == %d)\n", expectedState->numActions,
            testState->numActions);

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

    // TEST: Played cards should be identical
    error = 0;
    for (int i = 0; i < expectedState->playedCardCount; ++i) {
        if (expectedState->playedCards[i] != testState->playedCards[i]) {
            error = 1;
        }
    }
    assert_print(error == 0);
    printf(": Played cards pile contains correct cards\n");

    // TEST: Coins should be unchanged
    assert_print(expectedState->coins == testState->coins);
    printf(": Number of coins is correct (%d == %d)\n", expectedState->coins, testState->coins);

    // TEST: Number of buys should be unchanged
    assert_print(expectedState->numBuys == testState->numBuys);
    printf(": Number of buys is correct (%d == %d)\n", expectedState->numBuys, testState->numBuys);

}

void setTreasure(struct gameState *state, int numDeck, int numDiscard) {
    int numDeckFiller = 5;
    int numDiscardFiller = 5;
    int player = whoseTurn(state);

    for (int i = 0; i < MAX_DECK; ++i) {
        state->deck[player][i] = 0;
        state->discard[player][i] = 0;
    }

    // Put numDeck copper into deck, the remainder fill with smithy (placeholder)
    for (int i = 0; i < numDeck + numDeckFiller; ++i) {
        if (i >= numDeck) {
            state->deck[player][i] = smithy;
        } else {
            state->deck[player][i] = copper;
        }
    }
    state->deckCount[player] = numDeck + numDeckFiller;

    // Put numDiscard copper into discard, the remainder fill with smithy (placeholder)
    for (int i = 0; i < numDiscard + numDiscardFiller; ++i) {
        if (i >= numDiscard) {
            state->discard[player][i] = smithy;
        } else {
            state->discard[player][i] = copper;
        }
    }
    state->discardCount[player] = numDiscard + numDiscardFiller;
}

void drawTreasure(struct gameState *state) {
    int numTreasureDrawn = 0;
    int player = whoseTurn(state);
    int topOfDeckIdx, topOfDeck;
    int deckCount, discardCount;

    // Go through deck until we either get 2 treasure, or empty the deck
    while (state->deckCount[player] > 0 && numTreasureDrawn < 2) { 
        // Take top card off of the deck
        topOfDeckIdx = state->deckCount[player] - 1;
        topOfDeck = state->deck[player][topOfDeckIdx];
        state->deckCount[player]--;

        // If treasure --> hand, if not --> discard
        if (topOfDeck == copper || topOfDeck == silver || topOfDeck == gold) {
            state->hand[player][state->handCount[player]] = topOfDeck;
            state->handCount[player]++;
            numTreasureDrawn++;
        } else {
            state->discard[player][state->discardCount[player]] = topOfDeck;
            state->discardCount[player]++;
        }
    }

    // Stop if we already found 2
    if (numTreasureDrawn == 2) {
        return;
    }

    // Otherwise, put discard into deck and try one more time
    // Game method calls shuffle -- I'll be doing it manually.
    while (state->discardCount[player] > 0) {
        discardCount = state->discardCount[player];
        deckCount = state->deckCount[player];
        state->deck[player][deckCount] = state->discard[player][discardCount - 1];
        state->deckCount[player]++;
        state->discardCount[player]--;
    }

    // Go through deck one more time
    while (state->deckCount[player] > 0 && numTreasureDrawn < 2) { 
        // Take top card off of the deck
        topOfDeckIdx = state->deckCount[player] - 1;
        topOfDeck = state->deck[player][topOfDeckIdx];
        state->deckCount[player]--;

        // If treasure --> hand, if not --> discard
        if (topOfDeck == copper || topOfDeck == silver || topOfDeck == gold) {
            state->hand[player][state->handCount[player]] = topOfDeck;
            state->handCount[player]++;
            numTreasureDrawn++;
        } else {
            state->discard[player][state->discardCount[player]] = topOfDeck;
            state->discardCount[player]++;
        }
    }

    // That's it! No more drawing treasure. Time to go home.
    return;
}
