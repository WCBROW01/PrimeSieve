#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdatomic.h>
#include <unistd.h>
#include <pthread.h>

#include "bitops.h"
#include "primesieve.h"


#define min(a, b) ((a) > (b)) ? (b) : (a)
#define max(a, b) ((a) > (b)) ? (a) : (b)
#define next_multiple(a, b) (a) + ((b) - (a) % (b))

BitArray *primes;

static inline long lsqrt(long n) {
	n = labs(n);
	long x = n / 2;
	long xLast = x;
	long xLast2;

	do {
		xLast2 = xLast;
		xLast = x;
		x = (x + n / x) / 2;
	} while (x != xLast && x != xLast2);

	return x;
}

typedef struct MarkerThread {
	pthread_t thread;
	unsigned long check_end;
	atomic_ulong* check_barrier;
	/** Range start number, exclusive. */
	unsigned long range_start;
	/** Range end number, inclusive. */
	unsigned long range_end;
	unsigned long num_found;
} MarkerThread;

static void* marker_thread_fn(void* arg) {
	MarkerThread *tdata = (MarkerThread*) arg;

	long num = 3L;
	while (num <= tdata->check_end) {
		// Spinning here is fine, since it will very likely only be for a short while.
		long main_cursor = atomic_load_explicit(tdata->check_barrier, memory_order_acquire);

		while (num <= main_cursor) {
			if (CheckBit(primes, num / 2)) {
				unsigned long multiple = num * num;

				// Seek to this thread's assigned range
				if (multiple <= tdata->range_start) {
					multiple += next_multiple(tdata->range_start - multiple, 2 * num);
				}

				// Mark all multiples in this thread's assigned range
				for (; multiple <= tdata->range_end; multiple += 2 * num) {
					ClearBit(primes, multiple / 2);
				}
			}
			num += 2;
		}
	}

	// count up results
	tdata->num_found = countBits((tdata->range_start + 1) / 2, (tdata->range_end + 1) / 2, primes);
	return NULL;
}

/*
 * The range represented by a single item of the BitArray.
 * uint32_t represents 32 numbers, and since even numbers don't exist, this is doubled to 64.
 * Thread boundaries will be placed at multiples of this value such that each thread only touches
 * its own BitArray items.
 */
#define ATOM_SIZE 64

long findPrimes(long limit) {
	/* We are going to use a bit array to save on memory and make our code faster,
	 * so we will allocate an array based on the limit, excluding even numbers.
	 * Using limit + 1 helps avoid an off-by-one error.*/
	primes = makeBitArray((limit + 1) / 2, 0xFF);

	long thread_count = sysconf(_SC_NPROCESSORS_ONLN);

	// The main thread's assigned range ranges from 0 to main_range_end.
	// This is the last item (inclusive) that will be potentially written to by the main thread.
	unsigned long main_range_end = next_multiple(lsqrt(limit), ATOM_SIZE);

	// All remaining numbers will be marked by marker threads.
	unsigned long remaining_range = next_multiple(limit - main_range_end, ATOM_SIZE);

	// Only create as many threads as we need.
	thread_count = min(thread_count, remaining_range / ATOM_SIZE);

	printf("using %ld thread(s)\n", thread_count);
	MarkerThread threads[thread_count];
	memset(threads, 0, thread_count * sizeof(MarkerThread));

	// The largest number of which all multiples have been marked in the main thread's assigned
	// range. This will be used as a memory barrier for threads.
	atomic_ulong check_barrier = 2;

	// Create the threads!
	for (int i = 0; i < thread_count; i++) {
		threads[i].check_barrier = &check_barrier;
		threads[i].check_end = lsqrt(limit);
		threads[i].range_start = main_range_end + remaining_range / ATOM_SIZE * i / thread_count * ATOM_SIZE;
		threads[i].range_end = min(limit, main_range_end + remaining_range / ATOM_SIZE * (i + 1) / thread_count * ATOM_SIZE);

		int res = pthread_create(&threads[i].thread, NULL, &marker_thread_fn, &threads[i]);
		if (res != 0) {
			printf("FATAL: failed to create thread: %d\n", res);
			exit(-1);
		}
	}

	// Predefine values that we're skipping in the sieve.
	ClearBit(primes, 0);

	// Loop through all odd numbers up to the square root of limit
	for (long num = 3L; num <= lsqrt(limit); num += 2) {
		if (CheckBit(primes, num / 2)) {
			// Mark all odd multiples after square of prime
			for (long multiple = num * num; multiple <= main_range_end; multiple += 2 * num) {
				ClearBit(primes, multiple / 2);
			}

			atomic_store_explicit(&check_barrier, num, memory_order_release);
		}
	}

	// Signal that the main thread is done, and wait for threads to join.
	atomic_store_explicit(&check_barrier, lsqrt(limit), memory_order_release);
	long num_primes = countBits(0, (main_range_end + 1) / 2, primes) + 1;
	for (long i = 0; i < thread_count; i++) {
		pthread_join(threads[i].thread, NULL);
		num_primes += threads[i].num_found;
	}

	return num_primes;
}
