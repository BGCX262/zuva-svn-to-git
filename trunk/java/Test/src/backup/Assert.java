package backup;
public class Assert {
	public static void assertEquals(int actual, int expected) {
		String result = (actual == expected) ? "PASSED" : "FAILED";

		System.out.println("actual " + actual + " expected: " + expected);
		System.out.println("Test: " + result);
	}

	public static void assertEquals(int actual, int expected, String msg) {
		String result = (actual == expected) ? "PASSED" : "FAILED";
		System.out.println("\n" + msg);
		System.out.println("actual " + actual + " expected: " + expected);
		System.out.println("Test: " + result);
	}
}