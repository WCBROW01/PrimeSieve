import java.util.Arrays;

public class BitArray {
	
	final int INT_WIDTH = Integer.SIZE;
	final int[] BITMASKS = { 0x00000001, 0x00000002, 0x00000004, 0x00000008,
							 0x00000010, 0x00000020, 0x00000040, 0x00000080,
							 0x00000100, 0x00000200, 0x00000400, 0x00000800,
							 0x00001000, 0x00002000, 0x00004000, 0x00008000,
							 0x00010000, 0x00020000, 0x00040000, 0x00080000,
							 0x00100000, 0x00200000, 0x00400000, 0x00800000,
							 0x01000000, 0x02000000, 0x04000000, 0x08000000,
							 0x10000000, 0x20000000, 0x40000000, 0x80000000 };
	
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
		A[(int) (k/INT_WIDTH)] |= BITMASKS[(int) (k%INT_WIDTH)];
	}
	
	public void clearBit(long k) {
		A[(int) (k/INT_WIDTH)] &= ~BITMASKS[(int) (k%INT_WIDTH)];
	}
	
	public void flipBit(long k) {
		A[(int) (k/INT_WIDTH)] ^= BITMASKS[(int) (k%INT_WIDTH)];
	}
	
	public boolean checkBit(long k) {
		return (A[(int) (k/INT_WIDTH)] & BITMASKS[(int) (k%INT_WIDTH)]) != 0;
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
