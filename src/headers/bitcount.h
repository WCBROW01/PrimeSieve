#ifndef BITCOUNT_H
#define BITCOUNT_H

// LUT for the number of bits active for each byte value
static const char BITCOUNT[256] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3,
									3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4,
									3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
									3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5,
									3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3,
									3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
									3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3,
									3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
									3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
									6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4,
									3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4,
									4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5,
									3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5,
									5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4,
									3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4,
									4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
									3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
									6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7,
									6, 7, 7, 8 };

long countBits(int *bitArray, long limit) {
	// Cast bitarray to an unsigned char array so we can count each byte
	unsigned char *arrayBytes = (unsigned char*) bitArray;
	
	// Get # of contiguous bytes (quantity we can count fast without bitops)
	long fastCountLen = (limit + 1) / 8;
	
	// Count each byte by adding its value from the BITCOUNT LUT to numOn
	long numOn = 0L;
	for (long i = 0L; i < fastCountLen; i++)
		numOn += BITCOUNT[arrayBytes[i]];
	
	// Count the remaining bits bit by bit
	for (long i = fastCountLen * 8 + 1; i <= limit; i++)
		if (arrayBytes[i/8] & (BITMASKS[i%8]))
			numOn++;
	
	return numOn;
}

#endif
