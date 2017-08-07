CFLAGS = -Wno-implicit -fpic -coverage -lm

SHELL:=/bin/bash

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

unittestresults.out: all
	rm -f unittestresults.out
	$(foreach a, $(Tests), gcc -o testing asserttrue.c $(a) -g dominion.o rngs.o $(CFLAGS) ; \
	./testing &> unittestresults.out ;)
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo $(Tests)

#Tests = cardtest4.c

Tests:=$(shell ls  | egrep '*test[0-9]+.c' | sort -n  )

asserttrue.o: asserttrue.h asserttrue.c
		gcc -c asserttrue.c -g $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o asserttrue.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o asserttrue.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o asserttrue.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o asserttrue.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o asserttrue.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o asserttrue.o $(CFLAGS)

randomtestcard1.out: randomtestcard1
	./randomtestcard1 >> randomtestcard1.out
	gcov -c -b randomtestcard1.c >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	./randomtestcard2 >> randomtestcard2.out
	gcov -c -b randomtestcard2.c >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov -c -b randomtestadventurer.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out

randomtester0: randomtestadventurer randomtestadventurer.out
	@echo "COMPILING & RUNNING ADVENTURER TESTS"

randomtester1: randomtestcard1 randomtestcard1.out
	@echo "COMPILING & RUNNING COUNCIL ROOM TESTS"

randomtester2: randomtestcard2 randomtestcard2.out
	@echo "COMPILING & RUNNING SMITHY TESTS"

randomtestall: randomtester0 randomtester1 randomtester2
	@echo "COMPILING ALL RANDOM TESTER"

#I was planning on making a one command to rule them all but...
#time -p bash -c 'make clean && make randomtester0 && tail -n $(($(cat randomtestadventurer.c.gcov | wc -l)+15)) randomtestadventurer.out | head'
#time -p bash -c 'make clean && make randomtester1 && tail -n $(($(cat randomtestcard1.c.gcov | wc -l)+15)) randomtestcard1.out | head'
#time -p bash -c 'make clean && make randomtester2 && tail -n $(($(cat randomtestcard2.c.gcov | wc -l)+15)) randomtestcard2.out | head'

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so testDrawCard testDrawCard.exe
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer 

cleaner: clean
	rm -f *.out
