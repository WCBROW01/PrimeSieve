#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

#define SetBit(A,k)   ( A[k/32] |=  (BITMASKS[k%32]) )
#define ClearBit(A,k) ( A[k/32] &= ~(BITMASKS[k%32]) )
#define FlipBit(A,k)  ( A[k/32] ^=  (BITMASKS[k%32]) )
#define CheckBit(A,k) ( A[k/32] &   (BITMASKS[k%32]) )

// LUT for the number of bits active for each byte value
extern const char BITCOUNT[256];
extern const int32_t BITMASKS[32];

typedef struct {
	long length;
	long *list;
} BitList;

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
extern int32_t* makeBitArray(long length, char fillValue);

extern long countBits(int32_t *bitArray, long length);

// Creates an array, with each element being the numerical position of a 1.
extern BitList listBits(long length, int32_t *bitArray);

#endif
