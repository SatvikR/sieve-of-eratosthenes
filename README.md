# Sieve of Eratosthenes

This mini-project is an implementation of the [Sieve of Eratosthenes algorithm](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes), used to get all the primes under a threshold

## Build

### With make

```bash
make
```

### Without make

```bash
mkdir bin
gcc -o ./bin/primes src/primes.c -lm
```

## Run

### Run normally

```bash
./bin/primes
```

### Suppress output

```bash
./bin/primes --suppress-output
```
