/**
 * Interface defining the methods necessary for an
 * implementation of the Sieve of Eratosthenes
 * @author Will Brown
 * @version 1.0
 */
public interface PrimeSieveInterface {
	
	/**
	 * Main sieve method to find prime numbers.
	 * @param l the upper bound of the sieve
	 */
	public void findPrimes(long l);
	
	/**
	 * Get the results of the sieve as a list of integers.
	 * @return list of prime numbers
	 */
	public long[] listPrimes();
	
	/**
	 * Get the total number of primes.
	 * @return number of primes
	 */
	public int getNumPrimes();
}
