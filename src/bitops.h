#ifndef BITOPS_H
#define BITOPS_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SetBit(A,k)   ( A[k/32] |=  (BITMASKS[k%32]) )
#define ClearBit(A,k) ( A[k/32] &= ~(BITMASKS[k%32]) )
#define FlipBit(A,k)  ( A[k/32] ^=  (BITMASKS[k%32]) )
#define CheckBit(A,k) ( A[k/32] &   (BITMASKS[k%32]) )

static const int32_t BITMASKS[] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008,
									  0x00000010, 0x00000020, 0x00000040, 0x00000080,
									  0x00000100, 0x00000200, 0x00000400, 0x00000800,
									  0x00001000, 0x00002000, 0x00004000, 0x00008000,
									  0x00010000, 0x00020000, 0x00040000, 0x00080000,
									  0x00100000, 0x00200000, 0x00400000, 0x00800000,
									  0x01000000, 0x02000000, 0x04000000, 0x08000000,
									  0x10000000, 0x20000000, 0x40000000, 0x80000000 };

typedef struct {
	long length;
	long *list;
} BitList;

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
static inline int32_t* makeBitArray(long length, char fillValue) {
	long arrayLength = length / 32 + 1;
	int *bitArray = malloc(arrayLength * sizeof(int32_t));
	memset(bitArray, fillValue, (arrayLength * sizeof(int32_t)));
	
	return bitArray;
}

// Creates an array, with each element being the numerical position of a 1.
static BitList listBits(long length, int32_t *bitArray) {
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
