#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bitops.h"
#include "semiprimesieve.h"

void printSemiprimes(void) {
	BitList semiprimeList = listBits(numSemiprimes, semiprimes);
	printf("Semiprimes found: %ld", semiprimeList.list[0]);
	for (long i = 1L; i < semiprimeList.length; i++)
		printf(", %ld", semiprimeList.list[i]);

	printf("\n");
	free(semiprimeList.list);
}

void benchmark(long limit) {
	clock_t begin = clock();
	long numSemiprimes = findSemiprimes(limit);
	clock_t end = clock();
	long timeSpent = (end - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Time to complete: %ldms\n", timeSpent);
	printf("Number of semiprimes: %ld\n",   numSemiprimes);
}

int main(int argc, char *argv[]) {
	// The second argument is the limit of the sieve
	if (argc >= 2) {
		// begin sieve, using second arg as the limit for the sieve
		benchmark(atol(argv[1]));
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-semiprimes") == 0)
			printSemiprimes();

		free(semiprimes);

		return 0;
	} else {
		fprintf(stderr, "No limit provided.\n");
		return 1;
	}
}
