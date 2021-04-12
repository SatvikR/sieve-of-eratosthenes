//---------------------------------------------------------------------------
// Author: (c) Satvik Reddy 2021
// File: primes.c
// Description: Sieve of Eratosthenes implementation. The main algorithm
// starts at line 57
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#define MAX 100000
// fast integer ceiling devide
#define CEIL(x, y) (1 + ((x - 1) / y))


void set_bit(char *bits, int len, int index, bool value)
{
	assert(index < len);
	char *byte = &bits[index/8]; // byte in which the target bit lives

	if (value)
	{
		// set bit to 1
		*byte = *byte | (1 << ((8 * (index / 8 + 1)) - index - 1));
	}
	else
	{
		// This will set the bit to 0
		char n = 1 << ((8 * (index / 8 + 1)) - index - 1);
		*byte = *byte & (~n);
	}
	return;
}

bool get_bit(char *bits, int len, int index)
{
	assert(index < len);
	char *byte = &bits[index/8]; // byte in which the target bit lives

	return *byte & (1 << ((8 * (index / 8 + 1)) - index - 1));
}

void print_primes(char *c, int max)
{
	int bitlen = sizeof(char) * CEIL(max, 8) * 8;
	for (int i = 0; i < max; i++)
	{
		if (get_bit(c, bitlen, i))
			printf("%d, ", i + 1);
	}
	printf("\n\n");
}

char *primes(int max)
{
	int len    = CEIL(max, 8);           // length in bytes
	int bitlen = sizeof(char) * len * 8; // Length in bits (rounded up)
	char *bits = malloc(sizeof(char) * len);

	
	// set all bits to 1
	for (int i = 0; i < len; i++)
		bits[i] = ~0; // ~0 will flip 0x00000000 into 0x11111111
	
	// set 1 to not prime (1 is not prime)
	set_bit(bits, bitlen, 0, 0);
	double max_sqrt = sqrt(max);

	for (int i = 2; i <= max; i++) // 2 is the lowest prime
	{
		if (get_bit(bits, bitlen, i-1))
		{
			// If i is > max_sqrt than it's multiples will already be accounted for	
			if (max_sqrt <= i) 
			{
				set_bit(bits, bitlen, i-1, 1);	
			}
			else
			{
				for (int f = 2 * i; f <= max; f += i)
					set_bit(bits, bitlen, f - 1, 0);
			}
		}

	}

	return bits;
}

int main(int argc, char **argv)
{
	const char *print_flag = "--suppress-output";

	bool print;
	if (argc > 1)
		print = strcmp(argv[1], print_flag) == 0;

	clock_t t;
	t = clock();

	char *bits = primes(MAX);

	t = clock() - t;

	if (!print)
		print_primes(bits, MAX);

	free(bits);

	printf("primes(%d) took %.4f seconds (just the calculations, not the printing)\n", 
		MAX, ((float) t) / CLOCKS_PER_SEC);
	return 0;
}

