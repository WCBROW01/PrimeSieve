#ifndef PRIMESIEVE_H
#define PRIMESIEVE_H

#include <stdint.h>
#include "bitops.h"

extern long numPrimes;
extern BitArray *primes;

extern long findPrimes(long limit);

#endif
