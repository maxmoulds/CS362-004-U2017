CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

test_helpers.o: test_helpers.h test_helpers.c
	gcc -c test_helpers.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o test_helpers.o
	gcc -g -o unittest1 unittest1.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o test_helpers.o
	gcc -g -o unittest2 unittest2.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o test_helpers.o
	gcc -g -o unittest3 unittest3.c dominion.o rngs.o test_helpers.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -g -o unittest4 unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o test_helpers.o
	gcc -g -o cardtest1 cardtest1.c dominion.o rngs.o test_helpers.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o test_helpers.o
	gcc -g -o cardtest2 cardtest2.c dominion.o rngs.o test_helpers.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o test_helpers.o
	gcc -g -o cardtest3 cardtest3.c dominion.o rngs.o test_helpers.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o test_helpers.o
	gcc -g -o cardtest4 cardtest4.c dominion.o rngs.o test_helpers.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o test_helpers.o
	gcc -g -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o test_helpers.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o test_helpers.o
	gcc -g -o randomtestcard1 randomtestcard1.c dominion.o rngs.o test_helpers.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o test_helpers.o
	gcc -g -o randomtestcard2 randomtestcard2.c dominion.o rngs.o test_helpers.o $(CFLAGS)


randomtestresults: randomtestadventurer randomtestcard1 randomtestcard2

	echo "randomtestadventurer.c (Adventurer):" > randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b -c -f dominion.c >> randomtestadventurer.out

	echo "randomtestcard1.c (Smithy):" > randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	gcov -b -c -f dominion.c >> randomtestcard1.out

	echo "randomtestcard2.c (Great Hall):" >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	gcov -b -c -f dominion.c >> randomtestcard2.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Unit testing results:" > unittestresults.out
	
	echo "unittest1.c (buyCard):" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

	echo "unittest2.c (gainCard):" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

	echo "unittest3.c (cardCost):" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

	echo "unittest4.c (compare):" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

	echo "cardtest1.c (Smithy):" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

	echo "cardtest2.c (Great Hall):" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

	echo "cardtest3.c (Council Room):" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

	echo "cardtest4.c (Adventurer):" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	echo >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard
	rm -f unittest1 unittest2 unittest3 unittest4
	rm -f cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestadventurer randomtestcard1 randomtestcard2
