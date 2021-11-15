import java.util.Arrays;

/**
 * Optimized implementation of the Sieve of Eratosthenes.
 * @author Will Brown
 * @version 1.0
 */
public class PrimeSieve implements PrimeSieveInterface {

	static {
		System.loadLibrary("primesievejni");
	}

	/**
	 * Main sieve method to find prime numbers.
	 * @param limit the upper bound of the sieve
	 */
	public native void findPrimes(long limit);
	
	/**
	 * Get the results of the sieve as a list of integers.
	 * @return list of prime numbers
	 */
	public native long[] listPrimes();
	
	/**
	 * Get the total number of primes.
	 * @return number of primes
	 */
	public native int getNumPrimes();
	
}
