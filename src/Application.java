/**
 * Test application for the Sieve of Eratosthenes.
 * @author Will Brown
 * @version 1.0
 */
public class Application {
	
	public static void main(String[] args) {
		PrimeSieveInterface myPrimeSieve = new PrimeSieve();
		
		// The first argument is the limit of the sieve
		if (args.length >= 1) {
			// Get the execution time in milliseconds for the sieve.
			long startTime = System.currentTimeMillis();
			
			// begin sieve, using second arg as the limit for the sieve
			myPrimeSieve.findPrimes(Integer.parseInt(args[0]));
			System.out.println("Time to complete: " + (System.currentTimeMillis() - startTime) + "ms");
			
			// Print the number of primes it found for verification purposes.
			System.out.println("Number of primes: " + myPrimeSieve.getNumPrimes());
			
			// If there is a second argument, check if it is to print
			if (args.length >= 2 && args[1].equals("--print-primes"))
				printPrimes(myPrimeSieve.listPrimes());
		} else {
			System.out.println("No limit provided.");
			System.exit(1);
		}
	}
	
	private static void printPrimes(long[] primeList) {
		for (long number : primeList)
			System.out.print(number + " ");
	}

}
