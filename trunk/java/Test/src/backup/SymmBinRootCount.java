package backup;
public class SymmBinRootCount {
	private static int symmetricBinaryRootCount(int n) {
		for (int i = 1; i <= n / 2; i++) {
			// if(n == (i * bit_rev(i))) return i;
			if (n % i == 0) {
				if (n / i == bit_rev(i))
					return i;
			}
			// if(i%10000000 == 0) System.out.println("i= " + i);
		}

		return -1;
	}

	private static int bit_rev(int n) {
		String reversedBin = new StringBuffer(Integer.toBinaryString(n)).reverse().toString();
		int reversedInt = Integer.parseInt(reversedBin, 2);

		return reversedInt;
	}

	public static void tests() {
		Assert.assertEquals(bit_rev(25), 19);
		Assert.assertEquals(bit_rev(26), 11);
		Assert.assertEquals(bit_rev(11), 13);

		Assert.assertEquals(symmetricBinaryRootCount(50), 10);
		Assert.assertEquals(symmetricBinaryRootCount(286), 22);
		Assert.assertEquals(symmetricBinaryRootCount(3245), 55);
		Assert.assertEquals(symmetricBinaryRootCount(2147483646), 55);
		for (int i = 1; i <= 10000; i++)
			if (symmetricBinaryRootCount(i) != -1)
				System.out.println("JEST! " + i);

	}
}