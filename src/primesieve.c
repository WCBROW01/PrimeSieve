#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdatomic.h>
#include <unistd.h>
#include <pthread.h>

#include "bitops.h"
#include "primesieve.h"


#define max(a, b) ((a) > (b)) ? (a) : (b)

long numPrimes;
BitArray *primes;

static inline unsigned long lsqrt(long n) {
	unsigned long x = n / 2;
	unsigned long xLast;

	do {
		xLast = x;
		x = (x + n / x) / 2;
	} while (x != xLast);

	return x;
}

typedef struct MarkerThread {
	pthread_t thread;
	long num_end;
	long start_offset;
	long end_offset;
	uint32_t* primes;
	atomic_long* main_cursor;
} MarkerThread;

static void* marker_thread_fn(void* arg) {
	MarkerThread tdata = *((MarkerThread *)arg);
	printf("thread range %ld - %ld\n", tdata.start_offset, tdata.end_offset);
	long num = 3L;
	while (num < tdata.num_end) {
		long main_cursor = atomic_load_explicit(tdata.main_cursor, memory_order_acquire);
		while (num < main_cursor) {
			if (CheckBit(tdata.primes, num / 2)) {
				long multiple = num * num;
				while (multiple < tdata.start_offset) multiple += 2 * num;
				for (; multiple <= tdata.end_offset; multiple += 2 * num) {
					ClearBit(tdata.primes, multiple / 2);
				}
			}
			num += 2;
		}
	}
	return NULL;
}

long findPrimes(long limit) {
	/* We are going to use a bit array to save on memory and make our code faster,
	 * so we will allocate an array based on the limit, excluding even numbers. */
	primes = makeBitArray(limit / 2, 0xFF);

	int thread_count = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	printf("use %d threads\n", thread_count);
	MarkerThread* threads = calloc(thread_count, sizeof(MarkerThread));

	atomic_long main_cursor = 0;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for (int i = 0; i < thread_count; i++) {
		threads[i].primes = primes;
		threads[i].main_cursor = &main_cursor;
		threads[i].start_offset = max(lsqrt(limit), (limit / 32) * i / thread_count * 32);
		threads[i].end_offset = max(lsqrt(limit), (limit / 32) * (i + 1) / thread_count * 32);
		threads[i].num_end = lsqrt(limit);
		int res = pthread_create(&threads[i].thread, &attr, &marker_thread_fn, &threads[i]);
		if (res != 0) {
			printf("FATAL: failed to create thread: %d\n", res);
			exit(-1);
		}
	}
	pthread_attr_destroy(&attr);

	// Predefine values that we're skipping in the sieve.
	ClearBit(primes, 0);

	// Loop through all odd numbers up to the square root of limit
	for (long num = 3L; num <= lsqrt(limit); num += 2) {
		if (CheckBit(primes, num / 2)) {
			// Mark all odd multiples after square of prime
			for (long multiple = num * num; multiple <= lsqrt(limit); multiple += 2 * num) {
				ClearBit(primes, multiple / 2);
			}

			atomic_store_explicit(&main_cursor, num, memory_order_release);
		}
	}

	printf("waiting for threads to join...\n");
	atomic_store_explicit(&main_cursor, lsqrt(limit), memory_order_release);
	for (int i = 0; i < thread_count; i++) {
		pthread_join(threads[i].thread, NULL);
	}
	free(threads);

	numPrimes = countBits(limit / 2, primes) + 1;
	return numPrimes;
}
