#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bitops.h"

// LUT for the number of bits active for each byte value
const char BITCOUNT[256] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1,
							 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2,
							 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3,
							 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3,
							 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3,
							 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3,	3, 4, 3, 4,
							 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5,
							 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4,
							 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3,
							 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4,
							 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5,
							 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
							 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
							 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
							 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7,
							 8 };

const int32_t BITMASKS[32] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008,
							   0x00000010, 0x00000020, 0x00000040, 0x00000080,
							   0x00000100, 0x00000200, 0x00000400, 0x00000800,
							   0x00001000, 0x00002000, 0x00004000, 0x00008000,
							   0x00010000, 0x00020000, 0x00040000, 0x00080000,
							   0x00100000, 0x00200000, 0x00400000, 0x00800000,
							   0x01000000, 0x02000000, 0x04000000, 0x08000000,
							   0x10000000, 0x20000000, 0x40000000, 0x80000000 };

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
inline int32_t* makeBitArray(long length, char fillValue) {
	long arrayLength = length / 32 + 1;
	int32_t *bitArray = malloc(arrayLength * sizeof(int32_t));

	if (bitArray == NULL) {
		printf("Not enough memory to create bit array.\n");
		return NULL;
	}

	memset(bitArray, fillValue, (arrayLength * sizeof(int32_t)));

	// Zero out padding at the end
	int32_t lastBits = bitArray[arrayLength - 1];
    lastBits &= !((lastBits & -lastBits << 1) - 1);
    bitArray[arrayLength - 1] = lastBits;

	return bitArray;
}

long countBits(long length, int32_t *bitArray) {
	if (bitArray == NULL) {
		printf("Error counting bits. The bit array is null.\n");
		return 0;
	}

	// Cast bitarray to an unsigned char array so we can count each byte
	unsigned char *arrayBytes = (unsigned char*) bitArray;

	// Get # of contiguous bytes (quantity we can count fast without bitops)
	long arrayLength = length / 8 + 1;

	// Count each byte by adding its value from the BITCOUNT LUT to numOn
	long numOn = 0L;
	for (long i = 0L; i < arrayLength; i++)
		numOn += BITCOUNT[arrayBytes[i]];

	return numOn;
}

// Creates an array, with each element being the numerical position of a 1.
BitList listBits(long length, int32_t *bitArray) {
	BitList bitList;
	bitList.length = length;

	if (bitArray == NULL) {
		printf("Error listing bits. The bit array is null.");
		bitList.list = NULL;
		return bitList;
	}

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
