/**
 * Interface defining the methods necessary for an
 * implementation of the Sieve of Eratosthenes
 * @author Will Brown
 * @version 1.0
 */
public interface PrimeSieveInterface {
	
	/**
	 * Main sieve method to find prime numbers.
	 * @param limit the upper bound of the sieve
	 */
	public void findPrimes(int limit);
	
	/**
	 * Get the results of the sieve as a list of integers.
	 * @return list of prime numbers
	 */
	public int[] listPrimes();
	
	/**
	 * Get the total number of primes.
	 * @return number of primes
	 */
	public int getNumPrimes();
}
