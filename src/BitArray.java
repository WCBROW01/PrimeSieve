import java.util.Arrays;

public class BitArray {
	
	final int INT_WIDTH = Integer.SIZE;
	
	private int[] A;
	
	/**
	 * Allocate an array of ints based on the provided length.
	 * The length of the array will be divided by the length of an int.
	 * An extra entry is added because integers are usually rounded down.
	 * @param length length of the bit array
	 * @param fillValue value to fill the bit array with
	 */
	public BitArray(long length, int fillValue) {
		int arrayLength = (int) (length / INT_WIDTH) + 1;
		A = new int[arrayLength];
		Arrays.fill(A, fillValue);
	}
	
	public void setBit(long k) {
		A[(int) (k/INT_WIDTH)] |= (1 << (k%INT_WIDTH));
	}
	
	public void clearBit(long k) {
		A[(int) (k/INT_WIDTH)] &= ~(1 << (k%INT_WIDTH));
	}
	
	public void flipBit(long k) {
		A[(int) (k/INT_WIDTH)] ^= (1 << (k%INT_WIDTH));
	}
	
	public boolean checkBit(long k) {
		return (A[(int) (k/INT_WIDTH)] & (1 << (k%INT_WIDTH))) > 0;
	}
	
	/**
	 * Creates an array, with each element being the numerical position of a 1.
	 * @return list of bits that had a value of 1.
	 */
	public long[] listBits(int length) {
		long[] bitList = new long[length];
		long bitIndex = 0L;
		int listIndex = 0;
		while (listIndex < length) {
			if (checkBit(bitIndex)) {
				bitList[listIndex++] = bitIndex;
			} bitIndex++;
		}
		
		return bitList;
	}
	
}
