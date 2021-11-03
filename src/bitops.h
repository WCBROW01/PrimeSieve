#ifndef BITOPS_H
#define BITOPS_H

#define __STDC_WANT_IEC_60559_BFP_EXT__
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define SetBit(A,k)   ( A[k/INT_WIDTH] |=  (1 << (k%INT_WIDTH)) )
#define ClearBit(A,k) ( A[k/INT_WIDTH] &= ~(1 << (k%INT_WIDTH)) )
#define FlipBit(A,k)  ( A[k/INT_WIDTH] ^=  (1 << (k%INT_WIDTH)) )
#define CheckBit(A,k) ( A[k/INT_WIDTH] &   (1 << (k%INT_WIDTH)) )

typedef struct {
	long length;
	long *list;
} BitList;

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
static int* makeBitArray(long length, char fillValue) {
	long arrayLength = length / INT_WIDTH + 1;
	int *bitArray = malloc(arrayLength * sizeof(int));
	memset(bitArray, fillValue, (arrayLength * sizeof(int)));
	
	return bitArray;
}

// Creates an array, with each element being the numerical position of a 1.
static BitList listBits(long length, int *bitArray) {
	BitList bitList;
	bitList.length = length;
	bitList.list = malloc(length * sizeof(long));
	long listIndex = 0L;
	long bitIndex = 0L;
	while (listIndex < length) {
		if (CheckBit(bitArray, bitIndex)) {
			bitList.list[listIndex++] = bitIndex;
		} bitIndex++;
	}
	
	return bitList;
}

#endif
