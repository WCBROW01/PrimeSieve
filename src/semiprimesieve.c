#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bitops.h"
#include "primesieve.h"

long numSemiprimes = 0;
int *semiprimes;

void findSemiprimes(long limit) {
	findPrimes(limit);
	BitList primeList = listPrimes();
	
	/* We are going to use a bit array to save on memory and make our code faster,
	 * so we will allocate an array based on the limit and fill it with ones. */
	semiprimes = makeBitArray(limit + 1, 0);
	 
	long i = 0;
	long j = 0;
	long multiple = 0;
	for (i = 0L; i < primeList.length; i++) {
		for (j = i; j < primeList.length; j++) {
			multiple = primeList.list[i] * primeList.list[j];
			if (multiple <= limit) {
				if (!CheckBit(semiprimes, multiple)) {
					SetBit(semiprimes, multiple);
					numSemiprimes++;
				}
			} else break;
		}
	}	
	
	printf("Number of semiprimes: %ld\n", numSemiprimes);
}

/*
PrimeList listPrimes() {
	PrimeList myPrimeList;
	myPrimeList.numPrimes = numPrimes;
	myPrimeList.list = malloc(numPrimes * sizeof(long));
	long listIndex = 1;
	myPrimeList.list[0] = 2;
	for (long num = 3L; num <= limit; num += 2)
		if (CheckBit(primes, num))
			myPrimeList.list[listIndex++] = num;
	
	free(primes);
	return myPrimeList;
}
*/

int main(int argc, char *argv[]) {
	// The second argument is the limit of the sieve
	if (argc >= 2) {
		// begin sieve, using second arg as the limit for the sieve
		findSemiprimes(atol(argv[1]));
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			//printPrimes();
		
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
