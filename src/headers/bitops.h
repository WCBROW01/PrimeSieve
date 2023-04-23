#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>

#define SetBit(A,k)   (A[k/32] |= (BITMASKS[k%32]))
#define ClearBit(A,k) (A[k/32] &= (BITMASKS_INV[k%32]))
#define FlipBit(A,k)  (A[k/32] ^= (BITMASKS[k%32]))
#define CheckBit(A,k) (A[k/32] &  (BITMASKS[k%32]))

typedef uint32_t *BitArray;
typedef size_t *BitList;

// LUT for the number of bits active for each byte value
extern const uint32_t BITMASKS[32];
extern const uint32_t BITMASKS_INV[32];

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
BitArray makeBitArray(size_t length, unsigned char fillValue);

size_t countBits(BitArray bitArray, size_t start, size_t end);

// Creates an array, with each element being the numerical position of a 1.
BitList listBits(BitArray bitArray, size_t ba_len, size_t *bl_len);

#endif
