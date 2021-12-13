#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bitops.h"

// LUT for the number of bits active for each byte value
const uint8_t BITCOUNT[256] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
								1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
								1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
								2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
								1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
								2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
								2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
								3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
								1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
								2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
								2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
								3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
								2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
								3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
								3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
								4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
							  };

const uint32_t BITMASKS[32] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008,
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
BitArray *makeBitArray(long length, char fillValue) {
	long arrayLength = length / 32 + 1;
	BitArray *bitArray = malloc(arrayLength * sizeof(BitArray));

	if (bitArray == NULL) {
		fprintf(stderr, "Not enough memory to create bit array.\n");
		exit(1);
	}

	memset(bitArray, fillValue, (arrayLength * sizeof(BitArray)));

	// Zero out padding at the end
	bitArray[arrayLength - 1] &= BITMASKS[length % 32] - 1;

	return bitArray;
}

long countBits(long length, BitArray *bitArray) {
	assert(bitArray != NULL && "Error counting bits. The bit array is null.");

	// Cast bitArray to an unsigned 8-bit int array so we can count each byte
	uint8_t *arrayBytes = (uint8_t*) bitArray;

	// Get # of contiguous bytes (quantity we can count fast without bitops)
	long arrayLength = length / 8 + 1;

	// Count each byte by adding its value from the BITCOUNT LUT to numOn
	long numOn = 0L;
	for (long i = 0L; i < arrayLength; i++)
		numOn += BITCOUNT[arrayBytes[i]];

	return numOn;
}

// Creates an array, with each element being the numerical position of a 1.
BitList listBits(long length, BitArray *bitArray) {
	assert(bitArray != NULL && "Error listing bits. The bit array is null.");

	BitList bitList = {
		.length = length,
		.list	= malloc(length * sizeof(long))
	};

	long listIndex = 0L;
	long bitIndex = 0L;
	while (listIndex < length) {
		if (CheckBit(bitArray, bitIndex)) {
			bitList.list[listIndex++] = bitIndex;
		} bitIndex++;
	}

	return bitList;
}
