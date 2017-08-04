#include "dominion.h"

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#define MAX_TEST_ITER 1000

#define MIN_CARD curse
#define MAX_CARD treasure_map
#define MIN_KINGDOM_CARD adventurer
#define MAX_KINGDOM_CARD treasure_map

#define NUM_KINGDOM_CARDS 10

#define MIN_TEST_HAND 1
#define MIN_TEST_DECK 0
#define MIN_TEST_DISCARD 0
#define MAX_TEST_HAND 10
#define MAX_TEST_DECK MAX_DECK

#define MIN_TEST_PLAYERS 2
#define MAX_TEST_PLAYERS MAX_PLAYERS

#define MIN_TEST_NUM_ACTIONS 0
#define MAX_TEST_NUM_ACTIONS 10

#define MIN_TEST_NUM_BUYS 0
#define MAX_TEST_NUM_BUYS 10

#define MIN_TEST_COINS 0
#define MAX_TEST_COINS 10 


#define MIN_TEST_SEED 1
#define MAX_TEST_SEED MAX_TEST_ITER 
#define TEST_SEED 1

int assert_print(int condition);
int randInt(int low, int high);

#endif
