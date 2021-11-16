#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "bitops.h"
#include "primesieve.h"
#include "semiprimesieve.h"

long numSemiprimes;
int32_t *semiprimes;

long findSemiprimes(long limit) {
	numSemiprimes = 0;
	findPrimes(limit);
	BitList primeList = listBits(numPrimes, primes);
	
	/* We are going to use a bit array to save on memory and make our code faster,
	 * so we will allocate an array based on the limit and fill it with ones. */
	semiprimes = makeBitArray(limit + 1, 0);
	
	// Loop through primeList, multiplying each number with the rest of the list.
	for (long i = 0L; i < primeList.length; i++)
		for (long j = i, multiple;
			 (multiple = primeList.list[i] * primeList.list[j]) <= limit;
			 j++)
		{
			SetBit(semiprimes, multiple);
			numSemiprimes++;
		}
	
	free(primeList.list);
	return numSemiprimes;
}
