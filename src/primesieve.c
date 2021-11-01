#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

void findPrimes(long limit) {
	long numComposite = 1;
	bool *primes;
	primes = malloc((limit + 1) * sizeof(bool));
	memset(primes, 1, (limit + 1) * sizeof(bool));
	
	primes[0] = 0;
	primes[1] = 0;
	primes[2] = 1;
	
	for (long i = 4UL; i <= limit; i += 2) {
		primes[i] = 0;
		numComposite++;
	}
	
	for (long num = 3UL; num <= sqrt(limit); num += 2)
		if (primes[num])
			for (long multiple = num * num; multiple <= limit; multiple += 2 * num)
				if (primes[multiple]) {
					primes[multiple] = 0;
					numComposite++;
				}
	
	printf("Number of primes: %ld\n", limit - numComposite);
	
	free(primes);
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		clock_t begin = clock();
		findPrimes(atol(argv[1]));
		clock_t end = clock();
		long time_spent = (end - begin) / (CLOCKS_PER_SEC / 1000);
		printf("Time to complete: %ldms\n", time_spent);
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
