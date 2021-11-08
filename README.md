# PrimeSieve

An optimized (but not very well-optimized) implementation of the Sieve of Eratosthenes in both Java and C. The C implementation is currently much better.

### An explanation:

The Sieve of Eratosthenes is a fast algorithm for searching for prime numbers. It works by creating a list of numbers and marking them as composite (not prime). It will loop through every number, and if it has not marked a number yet, it will mark every multiple of that number (except itself) as composite. This results in every unmarked number being prime.

### How is this optimized?

#### The status of every number is stored as a single bit.

Normally, boolean values are stored as an entire byte because that is the smallest unit of memory that CPUs can address. Since only single bits are used, this decreases the memory usage by 8 times, not including any empty space at the end of the array. Time spent on memory allocation is also decreased as a result.

#### Every even number is marked beforehand.

This allows the main loop to only check whether odd numbers are prime, cutting the main loop in half. The memset call to fill the array uses an alternating sequence of bits, so even numbers are marked while the array is being created. (not even in a separate loop)

#### The inner loop starts at the square of the given prime.

All other multiples below this point are guaranteed to already have been marked, so they do not need to be checked. This removes a significant portion of the loop.

#### The inner loop only loops through odd multiples of the given prime.

Even-numbered multiples of any number are even, which means they are not prime, so we can skip them. This cuts the inner loop in half.

#### The outer loop only checks up to the square root of the limit.

Going any higher is unnecessary, since every number that we need to check has already been checked. The starting number of the inner loop would be higher than the limit, which would even throw an error.

### Common results for multiples of 10.

|   Input limit | Number of primes |
| ------------: | ---------------: |
|            10 |                4 |
|           100 |               25 |
|         1,000 |              168 |
|        10,000 |            1,229 |
|       100,000 |            9,592 |
|     1,000,000 |           78,498 |
|    10,000,000 |          664,579 |
|   100,000,000 |        5,761,455 |
| 1,000,000,000 |       50,847,534 |

Upper limit for the C implementation of this program: however long your longs are

### Build instructions (for C version)

Just run `make` and you should get a usable executable! There are no dependencies.
