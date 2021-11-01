#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

void findPrimes(long limit, bool printPrimes) {
	clock_t begin = clock();
	long numComposite = 1;
	bool *primes;
	primes = malloc((limit + 1) * sizeof(bool));
	memset(primes, 1, (limit + 1) * sizeof(bool));
	
	primes[0] = 0;
	primes[1] = 0;
	primes[2] = 1;
	
	for (long i = 4L; i <= limit; i += 2) {
		primes[i] = 0;
		numComposite++;
	}
	
	for (long num = 3L; num <= sqrt(limit); num += 2)
		if (primes[num])
			for (long multiple = num * num; multiple <= limit; multiple += 2 * num)
				if (primes[multiple]) {
					primes[multiple] = 0;
					numComposite++;
				}
	
	clock_t end = clock();
	long time_spent = (end - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Time to complete: %ldms\n", time_spent);
	
	printf("Number of primes: %ld\n", limit - numComposite);
	
	if (printPrimes) {
		printf("Primes found: 2");
		for (long i = 3L; i <= limit; i += 2)
			printf(", %d")
		printf("\n");
	}
	
	free(primes);
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		bool printPrimes = 0;
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			printPrimes = 1;		
		
		findPrimes(atol(argv[1]), printPrimes);
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
