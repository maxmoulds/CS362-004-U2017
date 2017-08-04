#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_helpers.h"
#include "dominion.h"
#include "dominion_helpers.h"

void testPlayCouncilRoom(void);
void runTestCases(struct gameState *expectedState, struct gameState *testState);

int main(int argv, char **argc) {
    testPlayCouncilRoom();
    return 0;
}

void testPlayCouncilRoom(void) {
    int seed = 1, numPlayers = 2;
    struct gameState testState, expectedState, cleanState;
    // These cards are arbitrarily chosen
    int kingdomCards[10] = { smithy, adventurer, village, mine, council_room,
        cutpurse, outpost, minion, steward, embargo };

    int handCount, deckCount, playedCardCount;

    // Create blank game state
    initializeGame(numPlayers, kingdomCards, seed, &testState);

    // Add Council Room card to player's hand
    int player = whoseTurn(&testState);
    int CouncilRoomPos = testState.handCount[player];
    testState.hand[player][CouncilRoomPos] = council_room;
    testState.handCount[player]++;

    memcpy(&expectedState, &testState, sizeof(struct gameState));
    memcpy(&cleanState,    &testState, sizeof(struct gameState));

    // Set expected state based on Council Room mechanics
    // Council Room should draw four cards and put them into the players hand

    /*
     *  CASE 1: More than 4 cards in player 0 deck, more than 1 card in player 1 deck
     */
    printf("\nCase 1 -- Player #0: > 4 cards. Player #1: > 1 card.\n");
    for (int i = 0; i < 4; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 2: Exactly 4 cards in player 0 deck, more than 1 card in player 1 deck
     */
    printf("\nCase 2 -- Player #0: == 4 cards. Player #1: > 1 card.\n");

    // Set deck count to 4, discard count to 0
    player = 0;
    testState.deckCount[player] = 4;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Draw the 4 remaining cards
    for (int i = 0; i < 4; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));
    /*
     *  CASE 3: Less than 4 cards in player 0 deck, more than 1 card in player 1 deck
     */
    printf("\nCase 3 -- Player #0: < 4 cards. Player #1: > 1 card.\n");
    
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

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 4: 0 cards in player 0 deck, more than 1 card in player 1 deck
     */
    printf("\nCase 4 -- Player #0: == 0 cards. Player #1: > 1 card.\n");
    
    // Set deck count to 0, discard count to 0
    player = 0;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset states
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 5: More than 4 cards in player 0 deck, exactly 1 card in player 1 deck
     */
    printf("\nCase 5 -- Player #0: > 4 cards. Player #1: == 1 card.\n");

    // Set player 2 deck count to 1, discard count to 0
    player = 1;
    testState.deckCount[player] = 1;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));
    player = 0;

    // Draw cards for Player #0
    for (int i = 0; i < 4; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 6: Exactly 4 cards in player 0 deck, more than 1 card in player 1 deck
     */
    printf("\nCase 6 -- Player #0: == 4 cards. Player #1: == 1 card.\n");

    // Set player 2 deck count to 1, discard count to 0
    player = 1;
    testState.deckCount[player] = 1;
    testState.discardCount[player] = 0;

    // Set deck count to 4, discard count to 0
    player = 0;
    testState.deckCount[player] = 4;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Draw the 4 remaining cards
    for (int i = 0; i < 4; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));
    /*
     *  CASE 7: Less than 4 cards in player 0 deck, more than 1 card in player 1 deck
     */
    printf("\nCase 7 -- Player #0: < 4 cards. Player #1: == 1 card.\n");
    
    // Set player 2 deck count to 1, discard count to 0
    player = 1;
    testState.deckCount[player] = 1;
    testState.discardCount[player] = 0;

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

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 8: 0 cards in player 0 deck, more than 1 card in player 1 deck
     */
    printf("\nCase 8 -- Player #0: == 0 cards. Player #1: == 1 card.\n");
    
    // Set player 2 deck count to 1, discard count to 0
    player = 1;
    testState.deckCount[player] = 1;
    testState.discardCount[player] = 0;

    // Set deck count to 0, discard count to 0
    player = 0;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset states
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 9: More than 4 cards in player 0 deck, 0 cards in player 1 deck
     */
    printf("\nCase 9 -- Player #0: > 4 cards. Player #1: == 0 cards.\n");

    // Set player 2 deck count to 0, discard count to 0
    player = 1;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));
    player = 0;

    // Draw cards for Player #0
    for (int i = 0; i < 4; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 10: Exactly 4 cards in player 0 deck, 0 cards in player 1 deck
     */
    printf("\nCase 10 -- Player #0: == 4 cards. Player #1: == 0 cards.\n");

    // Set player 2 deck count to 0, discard count to 0
    player = 1;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;

    // Set deck count to 4, discard count to 0
    player = 0;
    testState.deckCount[player] = 4;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Draw the 4 remaining cards
    for (int i = 0; i < 4; i++) {
        handCount = expectedState.handCount[player];
        deckCount = expectedState.deckCount[player];
        // Add top card of deck to end of hand
        expectedState.hand[player][handCount] = expectedState.deck[player][deckCount - 1];
        // Increment counters
        expectedState.handCount[player]++;
        expectedState.deckCount[player]--;
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));
    /*
     *  CASE 11: Less than 4 cards in player 0 deck, 0 cards in player 1 deck
     */
    printf("\nCase 11 -- Player #0: < 4 cards. Player #1: == 0 cards.\n");
    
    // Set player 2 deck count to 0, discard count to 0
    player = 1;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;

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

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset state
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));

    /*
     *  CASE 12: 0 cards in player 0 deck, 0 card in player 1 deck
     */
    printf("\nCase 12 -- Player #0: == 0 cards. Player #1: == 0 cards.\n");
    
    // Set player 2 deck count to 0, discard count to 0
    player = 1;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;

    // Set deck count to 0, discard count to 0
    player = 0;
    testState.deckCount[player] = 0;
    testState.discardCount[player] = 0;
    memcpy(&expectedState, &testState, sizeof(struct gameState));

    // Other players should draw a card
    for (int i = 0; i < expectedState.numPlayers; ++i) {
        if (i != player) {
            handCount = expectedState.handCount[i];
            deckCount = expectedState.deckCount[i];
            // Add top card of deck to end of hand
            expectedState.hand[i][handCount] = expectedState.deck[i][deckCount - 1];
            // Increment counters
            expectedState.handCount[i]++;
            expectedState.deckCount[i]--;
        }
    }

    // Number of buys should increase by 1
    expectedState.numBuys++;

    // Council Room should be placed in the played cards pile
    playedCardCount = expectedState.playedCardCount;
    expectedState.playedCards[playedCardCount] = expectedState.hand[player][CouncilRoomPos];
    expectedState.playedCardCount++;
    // Replace Council Room with last card in hand
    handCount = expectedState.handCount[player];
    expectedState.hand[player][CouncilRoomPos] = expectedState.hand[player][handCount - 1];
    expectedState.handCount[player]--;

    // Use playCouncilRoom to set testState
    playCouncilRoom(CouncilRoomPos, &testState);

    // Run test cases
    runTestCases(&expectedState, &testState);

    // Reset states
    memcpy(&testState,     &cleanState, sizeof(struct gameState));
    memcpy(&expectedState, &cleanState, sizeof(struct gameState));
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
