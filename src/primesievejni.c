#include "primesievejni.h"
#include "primesieve.h"

JNIEXPORT void JNICALL Java_PrimeSieve_findPrimes
  (JNIEnv *, jobject, jlong limit) {
	findPrimes(limit);
}

JNIEXPORT jlongArray JNICALL Java_PrimeSieve_listPrimes
  (JNIEnv *env, jobject) { 
	if (primes == NULL) {
		printf("Primes have not been generated yet.\n");
		return NULL;
	}
	
	BitList primeList = listBits(numPrimes, primes);
	free(primes);
	
	jlongArray newPrimeList = (*env)->NewLongArray(env, primeList.length);
	
	if (newPrimeList == NULL)
		return NULL; // out of memory error thrown
	
	(*env)->SetLongArrayRegion(env, newPrimeList, 0, primeList.length, primeList.list);
	free(primeList.list);
	return newPrimeList; 
}

JNIEXPORT jint JNICALL Java_PrimeSieve_getNumPrimes
  (JNIEnv *, jobject) {
	return numPrimes;
}
