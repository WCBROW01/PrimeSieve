#ifndef PRIMESIEVE_H
#define PRIMESIEVE_H

typedef struct {
	long numPrimes;
	long *list;
} PrimeList;

void findPrimes(long limit);
PrimeList listPrimes();

#endif
