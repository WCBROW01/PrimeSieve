#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>

// Macros for working with the integer bitfield.
#define SetBit(A,k)   ( A[k/32] |=  (1 << (k%32)) )
#define ClearBit(A,k) ( A[k/32] &= ~(1 << (k%32)) )
#define CheckBit(A,k) ( A[k/32] &   (1 << (k%32)) )

void findPrimes(long limit, bool printPrimes) {
	clock_t begin = clock();
	long numComposite = 1;
	/* We are going to use an array of integers as a bitfield to save on memory
	 * and make our code faster, so we will allocate an array based on the limit,
	 * but the length will be divided by 32. (since there are 32 bits in an int)
	 * making the number of bits the limit + 1 will make the rest of the code
	 * slightly more readable, but this is still harder to read than the Java code. */
	int *primes;
	primes = malloc(((limit + 1) / 32) * sizeof(int));
	// This sets every bit in the array to 1.
	memset(primes, INT_MAX, ((limit + 1) / 32) * sizeof(int));
	
	// Predefine values that we're skipping in the sieve.
	ClearBit(primes, 0);
	ClearBit(primes, 1);
	SetBit(primes, 2);
	
	// Mark all multiples of 2 as composite
	for (long num = 4L; num <= limit; num += 2) {
		ClearBit(primes, num);
		numComposite++;
	}
	
	// Loop through all odd numbers up to the square root of limit
	for (long num = 3L; num <= sqrt(limit); num += 2)
		if (CheckBit(primes, num))
			// Mark all odd multiples after square of prime
			for (long multiple = num * num; multiple <= limit; multiple += 2 * num)
				if (CheckBit(primes, multiple)) {
					ClearBit(primes, multiple);
					numComposite++;
				}
	
	clock_t end = clock();
	long time_spent = (end - begin) / (CLOCKS_PER_SEC / 1000);
	printf("Time to complete: %ldms\n", time_spent);
	
	printf("Number of primes: %ld\n", limit - numComposite);
	
	if (printPrimes) {
		printf("Primes found: 2");
		for (long num = 3L; num <= limit; num += 2)
			if (CheckBit(primes, num))
				printf(", %ld", num);
		
		printf("\n");
	}
	
	free(primes);
}

int main(int argc, char *argv[]) {
	// The second argument is the limit of the sieve
	if (argc >= 2) {
		bool printPrimes = 0;
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			printPrimes = 1;		
		
		// begin sieve, using second arg as the limit for the sieve
		findPrimes(atol(argv[1]), printPrimes);
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
