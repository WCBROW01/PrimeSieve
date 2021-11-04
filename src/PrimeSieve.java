import java.util.Arrays;

/**
 * Optimized implementation of the Sieve of Eratosthenes.
 * @author Will Brown
 * @version 1.0
 */
public class PrimeSieve implements PrimeSieveInterface {
	
	private BitArray primes;
	private int numPrimes;

	/**
	 * Main sieve method to find prime numbers.
	 * @param limit the upper bound of the sieve
	 */
	public void findPrimes(long limit) {
		long numComposite = limit / 2; // All multiples of 2 are already marked.
		
		/* We are going to use a bit array to save on memory and make our code faster,
		 * so we will allocate an array based on the limit and fill every byte with
		 * a value that pre-mark every even number. */
		primes = new BitArray(limit + 1, 0xaaaaaaaa);
		
		// Predefine values that we're skipping in the sieve.
		primes.clearBit(1L);
		primes.setBit(2L);
		
		// Loop through all odd numbers up to the square root of limit
		for (long num = 3L; num <= Math.sqrt(limit); num += 2)
			if (primes.checkBit(num))
				// Mark all odd multiples after square of prime
				for (long multiple = num * num; multiple <= limit; multiple += 2 * num)
					if (primes.checkBit(multiple)) {
						primes.clearBit(multiple);
						numComposite++;
					}
		
		numPrimes = (int) (limit - numComposite);
	}
	
	/**
	 * Get the results of the sieve as a list of integers.
	 * @return list of prime numbers
	 */
	public long[] listPrimes() {
		return primes.listBits(numPrimes);
	}
	
	/**
	 * Get the total number of primes.
	 * @return number of primes
	 */
	public int getNumPrimes() {
		return numPrimes;
	}
	
}
