# PrimeSieve

An optimized (but not very well-optimized) implementation of the Sieve of Eratosthenes.

### An explanation:

The Sieve of Eratosthenes is a fast algorithm for searching for prime numbers. It works by creating a list of numbers and marking them as composite (not prime). It will loop through every number, and if it has not marked a number yet, it will mark every multiple of that number (except itself) as composite. This results in every unmarked number being prime.

### How is this optimized?

#### Every even number is marked beforehand.

This allows the main loop to only check whether odd numbers are prime, cutting the main loop in half. Since the loop marking even numbers doesn’t need to execute any checks, this ends up being much faster.

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

Upper limit for this program: 2,147,391,110
