CC = clang++
CFLAGS = -c -std=c++20 -Werror -pedantic
DEBUG = -g
BOOSTPATH = -I /opt/homebrew/Cellar/boost/1.84.0_1/include
TESTLIB = /opt/homebrew/Cellar/boost/1.84.0_1/lib/libboost_unit_test_framework.a

all: test

test: test.o int_matrix.o xgcd.o algorithm.o
	$(CC) test.o int_matrix.o xgcd.o algorithm.o -o test $(TESTLIB)

test.o: test.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(BOOSTPATH) test.cpp 

int_matrix.o: int_matrix.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(BOOSTPATH) int_matrix.cpp

xgcd.o: xgcd.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(BOOSTPATH) xgcd.cpp

algorithm.o: algorithm.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(BOOSTPATH) algorithm.cpp

clean:
	rm *.o test
