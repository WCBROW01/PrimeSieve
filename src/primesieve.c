#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bitops.h"
#include "primesieve.h"

long numPrimes;
long limit;
int *primes;

void findPrimes(long newLimit) {
	limit = newLimit;
	long numComposite = 1;
	/* We are going to use a bit array to save on memory and make our code faster,
	 * so we will allocate an array based on the limit and fill it with ones. */
	 primes = makeBitArray(limit + 1, 1);
	
	// Predefine values that we're skipping in the sieve.
	ClearBit(primes, 0);
	ClearBit(primes, 1);
	
	// Mark all multiples of 2 as composite
	for (long num = 4L; num <= limit; num += 2) {
		ClearBit(primes, num);
		numComposite++;
	}
	
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

BitList listPrimes() {
	BitList primeList = listBits(numPrimes, primes);
	free(primes);
	return primeList;
}
