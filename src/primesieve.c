#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bitops.h"
#include "primesieve.h"

long numPrimes;
int *primes;

void findPrimes(long limit) {
	long numComposite = limit / 2; // All multiples of 2 are already marked.
	
	/* We are going to use a bit array to save on memory and make our code faster,
	 * so we will allocate an array based on the limit and fill every byte with
	 * a value that pre-mark every even number. */
	primes = makeBitArray(limit + 1, 0xaa);
	
	// Predefine values that we're skipping in the sieve.
	ClearBit(primes, 1);
	SetBit(primes, 2);
	
	// Loop through all odd numbers up to the square root of limit
	for (long num = 3L; num <= sqrt(limit); num += 2)
		if (CheckBit(primes, num))
			// Mark all odd multiples after square of prime
			for (long multiple = num * num; multiple <= limit; multiple += 2 * num)
				if (CheckBit(primes, multiple)) {
					ClearBit(primes, multiple);
					numComposite++;
				}
	
	numPrimes = limit - numComposite;
	printf("Number of primes: %ld\n", numPrimes);
}

BitList listPrimes(void) {
	BitList primeList = listBits(numPrimes, primes);
	free(primes);
	return primeList;
}
