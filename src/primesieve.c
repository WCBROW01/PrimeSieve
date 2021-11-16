#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "bitops.h"
#include "bitcount.h"
#include "primesieve.h"

long numPrimes;
int32_t *primes;

void countPrimes(long limit) {
	// Cast primes to an unsigned char array so we can count each byte
	unsigned char *primeBytes = (unsigned char*) primes;
	
	// Get # of contiguous bytes (ones we can count fast without bitops)
	long fastCountLen = (limit + 1) / 8;
	
	// Count each byte by adding its value from the BITCOUNT LUT to numPrimes
	numPrimes = 0L;
	for (long i = 0L; i < fastCountLen; i++)
		numPrimes += BITCOUNT[primeBytes[i]];
	
	// Count the remaining bits bit by bit
	for (long i = fastCountLen * 8 + 1; i <= limit; i++)
		if (primeBytes[i/8] & (BITMASKS[i%8]))
			numPrimes++;
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
	for (long num = 3L; num <= sqrt(limit); num += 2)
		if (CheckBit(primes, num))
			// Mark all odd multiples after square of prime
			for (long multiple = num * num; multiple <= limit; multiple += 2 * num)
				ClearBit(primes, multiple);
	
	countPrimes(limit);
	return numPrimes;
}

BitList listPrimes(void) {
	BitList primeList = listBits(numPrimes, primes);
	free(primes);
	return primeList;
}
