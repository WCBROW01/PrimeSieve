#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "bitops.h"
#include "primesieve.h"

static size_t numPrimes;

static void printPrimes(void) {
	size_t primeList_len;
	BitList primeList = listBits(primes, numPrimes - 1, &primeList_len);

	printf("Primes found: 2");
	for (long i = 0L; i < primeList_len; i++)
		printf(", %zd", 2 * primeList[i] + 1);

	printf("\n");
	free(primeList);
}

static void benchmark(size_t limit) {
	// Start clock
	struct timeval begin, end;
	gettimeofday(&begin, 0);

	numPrimes = findPrimes(limit);


	gettimeofday(&end, 0);
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	long timeSpent = (seconds + microseconds*1e-6) * 1e6;
	printf("Time to complete: %ldus\n", timeSpent);
	printf("Number of primes: %zd\n",   numPrimes);
}

int main(int argc, char *argv[]) {
	// The second argument is the limit of the sieve
	if (argc >= 2) {
		// begin sieve, using second arg as the limit for the sieve
		benchmark(atoll(argv[1]));
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			printPrimes();

		free(primes);
		return 0;
	} else {
		fprintf(stderr, "No limit provided.\n");
		return 1;
	}
}
