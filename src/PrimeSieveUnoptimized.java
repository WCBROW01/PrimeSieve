import java.util.Arrays;

/**
 * Basic unoptimized implementation of the Sieve of Eratosthenes.
 * @author Will Brown
 * @version 1.0
 */
public class PrimeSieveUnoptimized implements PrimeSieveInterface {
	
	private boolean[] primes;
	private int numPrimes;

	/**
	 * Main sieve method to find prime numbers.
	 * @param limit the upper bound of the sieve
	 */
	public void findPrimes(int limit) {
		int numComposite = 1;
		/*
		 * You most likely don't care about 0 anyways, but making the maximum index the value
		 * of the limit makes my life slightly easier for the purposes of writing this.
		 */
		primes = new boolean[limit + 1];
		Arrays.fill(primes, true);
		
		primes[0] = false;
		primes[1] = false;
		
		// Loop through all numbers (excluding 0 and 1) up to the limit
		for (int num = 2; num <= limit; num++)
			if (primes[num])
				// Mark all multiples excluding the prime number itself
				for (int multiple = num + num; multiple <= limit; multiple += num)
					if (primes[multiple]) {
						primes[multiple] = false;
						numComposite++;
					}
		
		// Get the number of primes from the quantity of composite numbers
		numPrimes = limit - numComposite;
	}
	
	/**
	 * Get the results of the sieve as a list of integers.
	 * @return list of prime numbers
	 */
	public int[] listPrimes() {
		int[] primeList = new int[numPrimes];
		/*
		 * You could loop through the entire array and get the same result,
		 * but this slightly hacky solution is faster.
		 */
		primeList[0] = 2;
		
		// Loop through only odd numbers to get primes.
		int index = 1;
		for (int num = 3; num < primes.length; num += 2)
			if (primes[num])
				primeList[index++] = num;
		
		return primeList;
	}
	
	/**
	 * Get the results of the sieve as a list of integers.
	 * Unoptimized method, to show that the sieve works completely properly.
	 * @return list of prime numbers
	 */
	public int[] listPrimesUnoptimized() {
		int[] primeList = new int[numPrimes];
		
		// Loop through all numbers to get primes.
		int index = 0;
		for (int num = 0; num < primes.length; num++)
			if (primes[num])
				primeList[index++] = num;
		
		return primeList;
	}
	
	/**
	 * Get the total number of primes.
	 * @return number of primes
	 */
	public int getNumPrimes() {
		return numPrimes;
	}
	
}
