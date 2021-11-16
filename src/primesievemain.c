#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "primesieve.h"

void printPrimes(void) {
	if (primes == NULL) {
		printf("Primes have not been generated yet.\n");
		return;
	}
	
	BitList primeList = listBits(numPrimes, primes);
	
	if (primeList.list == NULL) {
		printf("Failed to create prime list.\n");
		return;
	}
	
	printf("Primes found: %ld", primeList.list[0]);
	for (long i = 1L; i < primeList.length; i++)
		printf(", %ld", primeList.list[i]);
		
	printf("\n");
	free(primeList.list);
}

void benchmark(long limit) {
	clock_t begin = clock();
	long numPrimes = findPrimes(limit);
	clock_t end = clock();
	long timeSpent = (end - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Time to complete: %ldms\n", timeSpent);
	printf("Number of primes: %ld\n",   numPrimes);
}

int main(int argc, char *argv[]) {
	// The second argument is the limit of the sieve
	if (argc >= 2) {
		// begin sieve, using second arg as the limit for the sieve
		benchmark(atol(argv[1]));
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			printPrimes();
		
		free(primes);
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
