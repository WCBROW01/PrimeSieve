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

const uint32_t BITMASKS_INV[32] = { 0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFB, 0xFFFFFFF7,
									0xFFFFFFEF, 0xFFFFFFDF, 0xFFFFFFBF, 0xFFFFFF7F,
									0xFFFFFEFF, 0xFFFFFDFF, 0xFFFFFBFF, 0xFFFFF7FF,
									0xFFFFEFFF, 0xFFFFDFFF, 0xFFFFBFFF, 0xFFFF7FFF,
									0xFFFEFFFF, 0xFFFDFFFF, 0xFFFBFFFF, 0xFFF7FFFF,
									0xFFEFFFFF, 0xFFDFFFFF, 0xFFBFFFFF, 0xFF7FFFFF,
									0xFEFFFFFF, 0xFDFFFFFF, 0xFBFFFFFF, 0xF7FFFFFF,
									0xEFFFFFFF, 0xDFFFFFFF, 0xBFFFFFFF, 0x7FFFFFFF };

/* Allocate an array of ints based on the provided length.
 * The length of the array will be divided by the length of an int.
 * An extra entry is added because integers are usually rounded down. */
BitArray makeBitArray(size_t length, unsigned char fillValue) {
	long arrayLength = length / 32 + 1;
	BitArray bitArray = malloc(arrayLength * sizeof(*bitArray));
	if (!bitArray) return NULL;

	if (bitArray == NULL) {
		fprintf(stderr, "Not enough memory to create bit array.\n");
		exit(1);
	}

	memset(bitArray, fillValue, (arrayLength * sizeof(*bitArray)));

	// Zero out padding at the end
	bitArray[arrayLength - 1] &= BITMASKS[length % 32] - 1;

	return bitArray;
}

// Assumes that whatever segment you give it will only include whole bytes.
size_t countBits(BitArray bitArray, size_t start, size_t end) {
	assert(bitArray != NULL && "Error counting bits. The bit array is null.");

	// Cast bitArray to an unsigned 8-bit int array so we can count each byte
	uint8_t *arrayBytes = (uint8_t*) bitArray;

	// Get start and end as byte indices of the bit array
	start /= 8;
	// accounts for that bit at the end of the array that may not be a full segment
	end = end > end / 8 * 8 ? end / 8 + 1 : end / 8;

	// Count each byte by adding its value from the BITCOUNT LUT to numOn
	size_t numOn = 0;
	for (size_t i = start; i < end; i++)
		numOn += BITCOUNT[arrayBytes[i]];

	return numOn;
}

// Creates an array, with each element being the numerical position of a 1.
BitList listBits(BitArray bitArray, size_t ba_len, size_t *bl_len) {
	assert(bitArray != NULL && "Error listing bits. The bit array is null.");

	// compute size
	size_t length = 0;
	for (size_t bitIndex = 0; bitIndex < ba_len; bitIndex++)
		if (CheckBit(bitArray, bitIndex)) ++length;

	BitList bitList = malloc(length * sizeof(*bitList));
	if (!bitList) return NULL;
	for (size_t bitIndex = 0, listIndex = 0; listIndex < length; bitIndex++) {
		if (CheckBit(bitArray, bitIndex)) {
			bitList[listIndex++] = bitIndex;
		}
	}

	if (bl_len) *bl_len = length;
	return bitList;
}
