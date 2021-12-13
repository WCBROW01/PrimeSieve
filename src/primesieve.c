#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bitops.h"
#include "primesieve.h"

long numPrimes;
BitArray *primes;

static inline unsigned long lsqrt(long n) {
	unsigned long x = n / 2;
	unsigned long xLast;

	do {
		xLast = x;
		x = (x + n / x) / 2;
	} while (x != xLast);

	return x;
}

long findPrimes(long limit) {
	/* We are going to use a bit array to save on memory and make our code faster,
	 * so we will allocate an array based on the limit and fill every byte with
	 * a value that pre-mark every even number. */
	primes = makeBitArray(limit + 1, 0xaa);

	// Predefine values that we're skipping in the sieve.
	ClearBit(primes, 1);
	SetBit(primes, 2);

	// Loop through all odd numbers up to the square root of limit
	for (long num = 3L; num <= lsqrt(limit); num += 2)
		if (CheckBit(primes, num))
			// Mark all odd multiples after square of prime
			for (long multiple = num * num; multiple <= limit; multiple += 2 * num)
				ClearBit(primes, multiple);

	numPrimes = countBits(limit + 1, primes);
	return numPrimes;
}
