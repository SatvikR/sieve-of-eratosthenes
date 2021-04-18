//---------------------------------------------------------------------------
// Copyright (c) 2021 Satvik Reddy
// File: primes.c
// Description: Sieve of Eratosthenes implementation. The main algorithm
// starts at line 60
//---------------------------------------------------------------------------

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_MAX 1000000
// fast integer ceiling devide
#define CEIL(x, y) (1 + ((x - 1) / y))

inline void set_bit(uint8_t *bits, int len, int index, bool value)
{
    assert(index < len);
    uint8_t *byte = &bits[index / 8]; // byte in which the target bit lives

    if (value)
    {
        // set bit to 1
        *byte = *byte | (1 << ((8 * (index / 8 + 1)) - index - 1));
    }
    else
    {
        // This will set the bit to 0
        uint8_t n = 1 << ((8 * (index / 8 + 1)) - index - 1);
        *byte = *byte & (~n);
    }
    return;
}

inline bool get_bit(uint8_t *bits, int len, int index)
{
    assert(index < len);
    uint8_t *byte = &bits[index / 8]; // byte in which the target bit lives

    return *byte & (1 << ((8 * (index / 8 + 1)) - index - 1));
}

void print_primes(uint8_t *c, int max)
{
    int bitlen = sizeof(uint8_t) * CEIL(max, 8) * 8;
    for (int i = 0; i < max; i++)
    {
        if (get_bit(c, bitlen, i))
            printf("%d, ", i + 1);
    }
    printf("\n\n");
}

uint8_t *primes(int max)
{
    int len = CEIL(max, 8);                 // length in bytes
    int bitlen = sizeof(uint8_t) * len * 8; // Length in bits (rounded up)
    uint8_t *bits = malloc(sizeof(uint8_t) * len);

    // set all bits to 1
    for (int i = 0; i < len; i++)
        bits[i] = ~0; // ~0 will flip 0x00000000 into 0x11111111

    // set 1 to not prime (1 is not prime)
    set_bit(bits, bitlen, 0, 0);
    double max_sqrt = sqrt(max);

    for (int i = 2; i <= max_sqrt; i++) // 2 is the lowest prime
    {
        if (get_bit(bits, bitlen,
                    i - 1)) // Check if current bit is marked as 1 (prime)
        {
            for (int f = 2 * i; f <= max;
                 f += i) // Mark all multiples of i as 0 (not prime)
                set_bit(bits, bitlen, f - 1, 0);
        }
    }

    return bits;
}

int main(int argc, char **argv)
{
    const char *print_flag = "--suppress-output";
    const char *num_flag = "--num";
    const char *no_i_flag = "--no-i";

    bool print = false;
    bool interactive = true;
    int max = DEFAULT_MAX;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], print_flag) == 0)
            {
                print = true;
            }
            else if (strcmp(argv[i], num_flag) == 0)
            {
                if (i >= argc - 1)
                {
                    printf("Please provide a num with the --num flag");
                    exit(1);
                }
                else
                {
                    max = atoi(argv[i + 1]);
                    i++;
                }
            }
            else if (strcmp(argv[i], no_i_flag) == 0)
            {
                interactive = false;
            }
            else
            {
                printf("Argument \"%s\" is unknown\n", argv[i]);
                exit(1);
            }
        }
    }

    clock_t t;
    t = clock();

    uint8_t *bits = primes(max);

    t = clock() - t;

    if (!print)
        print_primes(bits, max);

    free(bits);

    printf("primes(%d) took %.4f seconds\n", max, ((float)t) / CLOCKS_PER_SEC);

    if (interactive)
    {
        printf("Press enter to exit...");
        while (getchar() != '\n')
            ;
    }

    return 0;
}
