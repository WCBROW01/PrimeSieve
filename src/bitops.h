#ifndef BITOPS_H
#define BITOPS_H

#include <limits.h>

#define INT_WIDTH ( sizeof(int) * 8 )

#define SetBit(A,k)   ( A[k/INT_WIDTH] |=  (1 << (k%INT_WIDTH)) )
#define ClearBit(A,k) ( A[k/INT_WIDTH] &= ~(1 << (k%INT_WIDTH)) )
#define CheckBit(A,k) ( A[k/INT_WIDTH] &   (1 << (k%INT_WIDTH)) )

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
static int* makeBitArray(long length, char initialValue) {
	long arrayLength = length / INT_WIDTH + 1;
	int *bitArray = malloc(arrayLength * sizeof(int));
	
	if (initialValue)
		memset(bitArray, INT_MAX, (arrayLength * sizeof(int)));
	else
		memset(bitArray, INT_MIN, (arrayLength * sizeof(int)));
	
	return bitArray;
}

#endif
