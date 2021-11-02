#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "primesieve.h"

void printPrimes() {
	PrimeList primeList = listPrimes();
	printf("Primes found: 2");
	for (long i = 1L; i < primeList.numPrimes; i++)
		printf(", %ld", primeList.list[i]);
		
	printf("\n");
}

int main(int argc, char *argv[]) {
	// The second argument is the limit of the sieve
	if (argc >= 2) {
		// begin sieve, using second arg as the limit for the sieve
		findPrimes(atol(argv[1]));
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			printPrimes();
		
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
