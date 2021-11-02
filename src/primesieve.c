#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define INT_WIDTH ( sizeof(int) * 8 )

// Macros for working with the integer bitfield.
#define SetBit(A,k)   ( A[k/INT_WIDTH] |=  (1 << (k%INT_WIDTH)) )
#define ClearBit(A,k) ( A[k/INT_WIDTH] &= ~(1 << (k%INT_WIDTH)) )
#define CheckBit(A,k) ( A[k/INT_WIDTH] &   (1 << (k%INT_WIDTH)) )

void findPrimes(long limit, bool printPrimes) {
	clock_t begin = clock();
	long numComposite = 1;
	/* We are going to use an array of integers as a bitfield to save on memory
	 * and make our code faster, so we will allocate an array based on the limit.
	 * The length of the array will be divided by the length of an int.
	 * Making the number of bits the limit + 1 will make the rest of the code
	 * slightly more readable, but this is still harder to read than the Java code. */
	int *primes;
	primes = malloc(((limit + 1) / INT_WIDTH) * sizeof(int));
	// This sets every bit in the array to 1.
	memset(primes, INT_MAX, ((limit + 1) / INT_WIDTH) * sizeof(int));
	
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
		bool printPrimes = false;
		// If there is a third argument, check if it is to print
		if (argc >= 3 && strcmp(argv[2], "--print-primes") == 0)
			printPrimes = true;		
		
		// begin sieve, using second arg as the limit for the sieve
		findPrimes(atol(argv[1]), printPrimes);
		return 0;
	} else {
		printf("No limit provided.\n");
		return 1;
	}
}
