#!/usr/bin/python3

from ctypes import *
import time
import sys

libprimesieve_so = "build/libprimesieve.so"

primesieve = CDLL(libprimesieve_so)

# Not working yet
def printPrimes():
	primeList = primesieve.listBits(primesieve.numPrimes, primesieve.primes)

	print("Primes found:", primeList.list[0], end='')
	for i in range(primeList.length):
		print(",", primeList.list[i], end='')

	print();

def benchmark(limit):
	begin = round(time.time() * 1000000)
	numPrimes = primesieve.findPrimes(limit)
	end = round(time.time() * 1000000)
	timeSpent = end - begin
	print("Time to complete: ", timeSpent, "us", sep='')
	print("Number of primes:", numPrimes)

def main():
	# The second argument is the limit of the sieve
	if len(sys.argv) >= 2:
		# begin sieve, using second arg as the limit for the sieve
		benchmark(int(sys.argv[1]));
		# If there is a third argument, check if it is to print
		if len(sys.argv) >= 3 and sys.argv[2] == "--print-primes":
			printPrimes();
	else:
		print("No limit provided.")

if __name__ == "__main__":
	main()
