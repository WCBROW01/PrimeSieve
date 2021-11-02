#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semiprimesieve.h"

void printSemiprimes() {
	BitList semiprimeList = listSemiprimes();
	printf("Primes found: 2");
	for (long i = 1L; i < semiprimeList.length; i++)
		printf(", %ld", semiprimeList.list[i]);
		
	printf("\n");
	free(semiprimeList.list);
}

int main(int argc, char *argv[]) {
	// The second argument is the limit of the sieve
	if (argc >= 2) {
		// begin sieve, using second arg as the limit for the sieve
		findSemiprimes(atol(argv[1]));
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			printSemiprimes();
		
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
