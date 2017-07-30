time -p bash -c 'make clean && make randomtester0 && tail -n $(($(cat randomtestadventurer.c.gcov | wc -l)+15)) randomtestadventurer.out | head'
time -p bash -c 'make clean && make randomtester1 && tail -n $(($(cat randomtestcard1.c.gcov | wc -l)+15)) randomtestcard1.out | head'
time -p bash -c 'make clean && make randomtester2 && tail -n $(($(cat randomtestcard2.c.gcov | wc -l)+15)) randomtestcard2.out | head'
