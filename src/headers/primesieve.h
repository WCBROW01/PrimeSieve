#ifndef PRIMESIEVE_H
#define PRIMESIEVE_H

#include "bitops.h"

static long numPrimes;
static int32_t *primes;

long findPrimes(long limit);
BitList listPrimes(void);

#endif
