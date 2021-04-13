CC=clang
CFLAGS=-Wall
ifneq ($(OS),Windows_NT)
	LFLAGS=-lm
endif

all: ./bin ./bin/primes

./bin/primes: ./src/primes.c 
	$(CC) $(CFLAGS) -o $@ $< $(LFLAGS)

./bin:
	@mkdir bin

clean:
	rm -r bin
