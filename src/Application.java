/**
 * Test application for the Sieve of Eratosthenes.
 * @author Will Brown
 * @version 1.0
 */
public class Application {

	public static void main(String[] args) {
		PrimeSieveInterface myPrimeSieve = new PrimeSieve();
		
		// Get the execution time in milliseconds for the sieve.
		long startTime = System.currentTimeMillis();
		myPrimeSieve.findPrimes(10000000);
		System.out.println("Time to complete: " + (System.currentTimeMillis() - startTime) + "ms");
		
		// Print the number of primes it found for verification purposes.
		System.out.println("Number of primes: " + myPrimeSieve.getNumPrimes());
		
		/* 
		 * Prints out every prime number found by the sieve
		 * (not recommended for extremely large quanities)
		 */
		//printPrimes(myPrimeSieve.listPrimes());
		
	}
	
	private static void printPrimes(int[] primeList) {
		for (int number : primeList)
			System.out.print(number + " ");
	}

}
