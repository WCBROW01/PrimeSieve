#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

#define SetBit(A,k)   ( A[k/32] |=  (BITMASKS[k%32]) )
#define ClearBit(A,k) ( A[k/32] &=  (BITMASKS_INV[k%32]) )
#define FlipBit(A,k)  ( A[k/32] ^=  (BITMASKS[k%32]) )
#define CheckBit(A,k) ( A[k/32] &   (BITMASKS[k%32]) )

typedef uint32_t BitArray;

// LUT for the number of bits active for each byte value
extern const uint8_t BITCOUNT[256];
extern const uint32_t BITMASKS[32];
extern const uint32_t BITMASKS_INV[32];

typedef struct {
	long length;
	long *list;
} BitList;

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
extern uint32_t* makeBitArray(long length, unsigned char fillValue);

extern long countBits(long length, uint32_t *bitArray);

// Creates an array, with each element being the numerical position of a 1.
extern BitList listBits(long length, uint32_t *bitArray);

#endif
