# Sieve of Eratosthenes

This mini-project is an implementation of the [Sieve of Eratosthenes algorithm](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes), used to get all the primes under a threshold

## Build

### With make

```bash
# Needs clang
make
```

### Without make

```bash
mkdir bin
clang -o ./bin/primes src/primes.c -lm # Remove -lm if on windows
```

## Run

### Run normally (uses 100,000 by default)

```bash
./bin/primes
```

### Run with other options

```bash
# --suppress-output will supress printing primes, but will keep time info
# --num lets you use a custom number
# --no-i will make it non interactive, (will exit automatically)
./bin/primes --suppress-output --num 100  --no-i 
```
