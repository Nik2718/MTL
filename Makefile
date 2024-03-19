CC = clang++
CFLAGS = -c -std=c++1z -Werror -pedantic
DEBUG = -g
BPATH = -I /opt/homebrew/Cellar/boost/1.84.0_1/include

all: test

test: test.o int_matrix.o
	$(CC) test.o int_matrix.o -o test

test.o: test.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(BPATH) test.cpp

int_matrix.o: int_matrix.cpp
	$(CC) $(DEBUG) $(CFLAGS) $(BPATH) int_matrix.cpp

clean:
	rm *.o test