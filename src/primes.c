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

#define MAX 120
// fast integer ceiling devide
#define CEIL(x, y) 1 + ((x - 1) / y)


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
	for (int i = 0; i < bitlen; i++)
	{
		if (get_bit(c, bitlen, i))
			printf("%d, ", i + 1);
	}
	printf("\n");
}

char *primes(int max)
{
	// Length of our bit array
	int len = CEIL(max, 8);
	int bitlen = sizeof(char) * len * 8;
	// Create bit array	
	//char bits[len];
	char *bits = malloc(sizeof(char) * len); // len bytes

	
	// set all bits to 1
	for (int i = 0; i < len; i++)
		bits[i] = ~0; // ~0 will flip 0x00000000 into 0x11111111
	
	double max_sqrt = sqrt(max);

	for (int i = 2; i <= bitlen; i++) // 2 is the lowest prime
	{
		if (get_bit(bits, bitlen, i-1))
		{
			if (max_sqrt <= i) // If i is > max_sqrt than it's multiples will already be accounted for	
			{
				set_bit(bits, bitlen, i-1, true);	
			}
			else
			{
				for (int f = 2 * i; f <= bitlen; f += i)
					set_bit(bits, bitlen, f - 1, false);
			}
		}

	}

	return bits;
}

int main(int argc, char **argv)
{
	char *bits = primes(MAX);

	print_primes(bits, MAX);

	free(bits);
	return 0;
}

