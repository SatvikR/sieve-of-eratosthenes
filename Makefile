CC=gcc
CFLAGS=-Wall
LFLAGS=-lm

all: ./bin ./bin/primes

./bin/primes: ./src/primes.c 
	$(CC) $(CFLAGS) -o $@ $< $(LFLAGS)

./bin:
	@mkdir bin

clean:
	rm -r bin
