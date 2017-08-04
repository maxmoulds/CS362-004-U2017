/******************************************************************************
 * This code implements a random test generator for Adventurer.               *
 * Randomized pieces of game state include:                                   *
 *  - Number of players in game                                               *
 *  - Whose turn it is                                                        *
 *  - The number of actions & buys available                                  *
 *  - Which Kingdom cards are in play                                         *
 *  - The number, type, and order of cards in a player's hand                 *
 *  - The number, type, and order of cards in a player's discard              *
 *  - The number, type, and order of cards in a player's deck                 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test_helpers.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void randomizeGameState(struct gameState *state, int cardUnderTest);
void randomizePlayerCards(struct gameState *state);
void setExpectedGameState(struct gameState *state);
int testGameState(struct gameState *expected, int cardPosn);

int main(int argv, char **argc) {
    
    struct gameState testState;
    int cardUnderTest = adventurer;
    int testResult = 0, passedTestCount = 0;

    for (int testCase = 0; testCase < MAX_TEST_ITER; ++testCase) {
        randomizeGameState(&testState, cardUnderTest);

        // Set phase to action
        testState.phase = 0; // NOTE: phase variable values is not well documented 

        // Put card under test into random location in current players hand
        int player = whoseTurn(&testState);
        int cardPosn = randInt(0, testState.handCount[player]);
        testState.hand[player][cardPosn] = cardUnderTest;

        // Run the test
        testResult = testGameState(&testState, cardPosn);
        assert_print(testResult);
        printf(": Test Case #%d\n", testCase);
        if (testResult) { passedTestCount++; }
    }

    printf("TOTAL PASSING TESTS: %d/%d\n\n", passedTestCount, MAX_TEST_ITER);

    return 0;
}

// Set up initial game state randomly
// cardUnderTest is a required card, must be available in Kingdom cards
void randomizeGameState(struct gameState *state, int cardUnderTest) {
    // Zero out the state in memory
    memset(state, 0, sizeof(struct gameState));

    // Randomly select the Kingdom cards
    int kingdomCards[NUM_KINGDOM_CARDS];
    int cardIsChosen[MAX_KINGDOM_CARD + 1] = { 0 };
    int numCardsChosen = 0, randCard = 0;
    while (numCardsChosen < NUM_KINGDOM_CARDS - 1) {
        randCard = randInt(MIN_KINGDOM_CARD, MAX_KINGDOM_CARD); 
        if (!cardIsChosen[randCard] && randCard != cardUnderTest) {
            cardIsChosen[randCard] = 1;
            kingdomCards[numCardsChosen] = randCard;
            ++numCardsChosen;
        }
    }

    // Last Kindgom card is the mandatory one
    kingdomCards[NUM_KINGDOM_CARDS - 1] = cardUnderTest;

    int numPlayers = randInt(MIN_TEST_PLAYERS, MAX_TEST_PLAYERS);
    int seed = randInt(MIN_TEST_SEED, MAX_TEST_SEED);
    int status = initializeGame(numPlayers, kingdomCards, seed, state);

    assert(status == 0);

    // Randomize each players hand
    randomizePlayerCards(state);

    // Randomize whose turn it is
    state->whoseTurn = randInt(0, state->numPlayers - 1);

    // Randomize numActions / numBuys / coins
    state->numActions = randInt(MIN_TEST_NUM_ACTIONS, MAX_TEST_NUM_ACTIONS);
    state->numBuys = randInt(MIN_TEST_NUM_BUYS, MAX_TEST_NUM_BUYS);
    state->coins = randInt(MIN_TEST_COINS, MAX_TEST_COINS);
}

void randomizePlayerCards(struct gameState *state) {
    
    int randCard = 0;

    // Start with hand...
    for (int player = 0; player < state->numPlayers; ++player) {

        // Random number of cards in hand
        state->handCount[player] = randInt(MIN_TEST_HAND, MAX_TEST_HAND);

        for (int i = 0; i < state->handCount[player]; ++i) {
            // Draw random cards until we find one with non-empty supply (i.e., is in game)
            do {
                randCard = randInt(MIN_CARD, MAX_CARD); 
            } while (state->supplyCount[randCard] < 0);
            state->hand[player][i] = randCard;
        }
    }

    // ...then deck...
    int maxDeckCount = 0;
    for (int player = 0; player < state->numPlayers; ++player) {

        // Make sure we don't overrun the maximum number of cards
        maxDeckCount = MAX_TEST_DECK - state->handCount[player];
        // Random number of cards in deck
        state->deckCount[player] = randInt(MIN_TEST_DECK, maxDeckCount);

        for (int i = 0; i < state->deckCount[player]; ++i) {
            // Draw random cards until we find one with non-empty supply (i.e., is in game)
            do {
                randCard = randInt(MIN_CARD, MAX_CARD); 
            } while (state->supplyCount[randCard] < 1);
            state->deck[player][i] = randCard;
        }
    }

    // ...and finally, discard.
    int maxDiscardCount = 0;
    for (int player = 0; player < state->numPlayers; ++player) {
        
        // Make sure we don't overrun the maximum number of cards
        maxDiscardCount = MAX_TEST_DECK - state->handCount[player] - state->deckCount[player];
        // Random number of cards in discard
        state->discardCount[player] = randInt(MIN_TEST_DISCARD, maxDiscardCount);

        for (int i = 0; i < state->discardCount[player]; ++i) {
            // Draw random cards until we find one with non-empty supply (i.e., is in game)
            do {
                randCard = randInt(MIN_CARD, MAX_CARD);
            } while (state->supplyCount[randCard] < 0);
            state->discard[player][i] = randCard;
        }
    }

    return;
}

void setExpectedGameState(struct gameState *state) {

}

// 1 == passing test
// 0 == failing test
int testGameState(struct gameState *testState, int cardPosn) {
    
    struct gameState expectedState;

    // Copy initial state
    memcpy(&expectedState, testState, sizeof(struct gameState));

    // Reset random seed
    PutSeed((long)TEST_SEED);

    // Play card manually
    int player = whoseTurn(&expectedState);

    // Move the card under test to the playedCards pile
    int handCount = expectedState.handCount[player];
    expectedState.playedCards[expectedState.playedCardCount] = expectedState.hand[player][cardPosn];
    expectedState.playedCardCount++;
    // Replace card under test with last card in hand
    expectedState.hand[player][cardPosn] = expectedState.hand[player][handCount - 1];
    expectedState.hand[player][handCount - 1] = -1;
    expectedState.handCount[player]--;

    // Set a counter for the maximum number of cards we could possibly have to draw before we'll
    //  have drawn every card at least once.
    int numTreasure = 0, numNonTreasure = 0;
    int nonTreasureCards[MAX_DECK] = {-1};
    int card = 0;
    int status = 0;

    while (numTreasure < 2) {
        // Draw a card
        status = drawCard(player, &expectedState);

        // If unable to draw another card, deck + discard is empty (we checked all cards)
        if (status != 0) {
            break;
        }

        // Last card in hand is the card we drew
        card = expectedState.hand[player][expectedState.handCount[player] - 1];
        if (card == copper || card == silver || card == gold) {
            ++numTreasure;
        } else {
            // Store this card off to the side
            nonTreasureCards[numNonTreasure] = card; 
            numNonTreasure++;
            // Remove it from the players hand
            expectedState.hand[player][expectedState.handCount[player] - 1] = -1;
            expectedState.handCount[player]--;
        }
    }

    // Put the non-treasure cards in the discard
    while (numNonTreasure - 1 >= 0) {
        // Pull off the top non-treasure card
        card = nonTreasureCards[numNonTreasure - 1];
        numNonTreasure--;

        // ...and put it in the discard pile
        expectedState.discard[player][expectedState.discardCount[player]] = card;
        expectedState.discardCount[player]++;
    }

    // Reset random seed
    PutSeed((long)TEST_SEED);

    // Play card using FUT
    status = playAdventurer(testState);
    // non-zero return value means FUT did not execute correctly
    if (status != 0) {
        return 0; // 0 in this context means "false" (did not pass)
        
    }

    // Test result passes if memory of expectedState and testState are idenitical
    return memcmp(&expectedState, testState, sizeof(struct gameState)) == 0;
}
