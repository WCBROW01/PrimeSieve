#ifndef PRIMESIEVE_H
#define PRIMESIEVE_H

#include <stdint.h>
#include "bitops.h"

extern BitArray primes;

extern size_t findPrimes(size_t limit);

#endif
