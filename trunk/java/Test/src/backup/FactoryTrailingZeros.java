package backup;
/**
 * http://en.wikipedia.org/wiki/Trailing_zero
 */
import java.math.BigInteger;

public class FactoryTrailingZeros {
	private static int factTrailingZeros(int input) {
		int sum = 0;
		for (int i = 5; i <= input; i *= 5) {
			sum += Math.floor(input / i);
		}

		return sum;
	}

	// alternative longer solution
	public long factTrailingZeros1(int input) {
		BigInteger result = BigInteger.ONE;
		for (int i = 2; i <= input; i++) {
			result = result.multiply(BigInteger.valueOf(i));
			// if(result.remainder(BigInteger.TEN).compareTo(BigInteger.ZERO) ==
			// 0) result = result.divide(BigInteger.valueOf(10));
		}

		System.out.println("Silnia z " + input + " : " + result);

		int sum = 0;
		String strSum = result.toString();
		for (int i = strSum.length() - 1; strSum.charAt(i) == '0'; i--, sum++)
			;

		return sum;
	}

	public static void tests() {
		Assert.assertEquals(factTrailingZeros(1), 0);
		Assert.assertEquals(factTrailingZeros(2), 0);
		Assert.assertEquals(factTrailingZeros(5), 1);
		Assert.assertEquals(factTrailingZeros(7), 1);
		Assert.assertEquals(factTrailingZeros(9), 1);
		Assert.assertEquals(factTrailingZeros(10), 2);
		Assert.assertEquals(factTrailingZeros(26), 6);
		Assert.assertEquals(factTrailingZeros(60), 14);
		Assert.assertEquals(factTrailingZeros(130), 32);
		Assert.assertEquals(factTrailingZeros(1000), 249);
		Assert.assertEquals(factTrailingZeros(10000), 2499);
	}
}